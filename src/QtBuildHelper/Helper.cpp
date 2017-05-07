#include <iostream>

#include <QStringList>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#include "Helper.h"

namespace Helper
{
  static const QString dateTimeFormat = "yyyy-MM-dd hh:mm:ss";
  static const QString mapSeperator = " --> ";

  QString toString(const QDateTime& dateTime)
  {
    return dateTime.toString(dateTimeFormat);
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

  bool stringMapToFile(const QMap<QString, QString>& map, const QString& filePath)
  {
    QStringList stringList;

    for (auto it = map.begin(); it != map.end(); ++it)
    {
      stringList.append(QString("%1%2%3").arg(it.key()).arg(mapSeperator).arg(it.value()));
    }

    return stringListToFile(stringList, filePath);
  }

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

  void showMessage(const std::string& message)
  {
    std::cout << message << std::endl;
  }

  void showError(const std::string& error)
  {
    std::cout << "ERROR:   " << error << std::endl;
  }

  QString fileName(const QString& filePath)
  {
    QStringList stringList = filePath.split("/");

    return stringList.isEmpty() ? QString() : stringList.last();
  }

  void removeExcludedTools(QList<Tool>& tools, const QStringList& excludedTools)
  {
    if (!excludedTools.isEmpty())
    {
      for (auto& excludedTool : excludedTools)
      {
        for (int i = 0; i < tools.length(); ++i)
        {
          if (tools[i].m_toolName.toLower() == excludedTool.toLower())
          {
            tools.removeAt(i);
            break;
          }
        }
      }
    }
  }
}
