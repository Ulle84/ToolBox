#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QCryptographicHash>

#include "QStringEx.h"

#include "File.h"

static const QString mapSeperator = " --> ";

namespace File
{
  QString fileToString(const QString& fileName)
  {
    QString fileContent;

    QFile file(fileName);

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

  QStringList fileToStringList(const QString& fileName)
  {
    return fileToString(fileName).split("\n");
  }

  QMap<QString, QString> fileToStringMap(const QString& fileName)
  {
    QMap<QString, QString> map;

    QStringList stringList = fileToStringList(fileName);

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

  bool stringToFile(const QString& fileContent, const QString& fileName)
  {
    QFile file(fileName);

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

  bool stringListToFile(const QStringList& fileContent, const QString& fileName)
  {
    return stringToFile(fileContent.join("\n"), fileName);
  }

  QString directory(const QString& fileName)
  {
    int max = std::max(fileName.lastIndexOf('/'), fileName.lastIndexOf('\\'));

    if (max == -1)
    {
      return QString();
    }

    return fileName.left(max);
  }

  bool stringMapToFile(const QMap<QString, QString>& map, const QString& fileName)
  {
    QStringList stringList;

    for (auto it = map.begin(); it != map.end(); ++it)
    {
      stringList.append(QString("%1%2%3").arg(it.key()).arg(mapSeperator).arg(it.value()));
    }

    return stringListToFile(stringList, fileName);
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

  QStringList SHARED_API merge(const QStringList& fileNames)
  {
    QStringList combined;

    for (auto& it : fileNames)
    {
      combined.append(fileToStringList(it));
    }

    return combined;
  }

}