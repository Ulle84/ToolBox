#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QCryptographicHash>

#include "QStringEx.h"

#include "FileOld.h"
#include "Path.h"

namespace FileOld
{
  static const QString mapSeperator = " --> ";

  QString fileToString(const QString& filePath)
  {
    QString fileContent;

    QFile file(filePath);

    if (file.exists())
    {
      if (file.open(QFile::ReadOnly | QFile::Text))
      {
        QTextStream textStream(&file);
        textStream.setCodec("UTF-8");
        fileContent = textStream.readAll();
        file.close();
      }
    }

    return fileContent;
  }

  QStringList fileToStringList(const QString& filePath)
  {
    return fileToString(filePath).split("\n");
  }

  QMap<QString, QString> fileToStringMap(const QString& filePath)
  {
    QMap<QString, QString> map;

    QStringList stringList = fileToStringList(filePath);

    for (auto it : stringList)
    {
      QStringList splitted = it.split(mapSeperator, QString::KeepEmptyParts);

      if (splitted.length() != 2)
      {
        continue;
      }

      map[splitted[0]] = splitted[1];
    }

    return map;
  }

  bool stringToFile(const QString& fileContent, const QString& filePath)
  {
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QFile::Text))
    {
      QTextStream textStream(&file);
      textStream.setCodec("UTF-8");
      textStream << fileContent;

      file.close();
      return true;
    }
    else
    {
      return false;
    }
  }

  bool stringListToFile(const QStringList& fileContent, const QString& filePath)
  {
    return stringToFile(fileContent.join("\n"), filePath);
  }

  QString directory(const QString& filePath)
  {
    int max = std::max(filePath.lastIndexOf('/'), filePath.lastIndexOf('\\'));

    if (max == -1)
    {
      return QString();
    }

    return filePath.left(max);
  }

  bool stringMapToFile(const QMap<QString, QString>& map, const QString& filePath)
  {
    QStringList stringList;

    for (auto it = map.begin(); it != map.end(); ++it)
    {
      stringList.append(QString("%1%2%3").arg(it.key()).arg(mapSeperator).arg(it.value()));
    }

    return stringListToFile(stringList, filePath);
  }

  QString checkSum(const QString& fileName)
  {
    QFile file(fileName);

    if (file.open(QFile::ReadOnly))
    {
      QCryptographicHash hash(QCryptographicHash::Md5);

      if (hash.addData(&file))
      {
        QString string(hash.result().toBase64());
        QStringEx::removeTrailingSigns(string, '=');
        return string;
      }
    }

    return QString();
  }

  QStringList SHARED_API merge(const QStringList& filePaths)
  {
    QStringList combined;

    for (auto& it : filePaths)
    {
      combined.append(fileToStringList(it));
    }

    return combined;
  }

  QString name(const QString& filePath)
  {
    QStringList splitted = Path::split(filePath);

    if (splitted.isEmpty())
    {
      return QString();
    }

    return splitted.last();
  }
}