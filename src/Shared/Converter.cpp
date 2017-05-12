// created on 2016-12-15 by Ulrich Belitz

#include <QJsonDocument>
#include <QString>
#include <QJsonObject>
#include <QFile>

#include "Converter.h"
#include "File.h"
#include "Path.h"
#include "SmlConverter.h"

namespace Converter
{
  std::string toStdString(int number)
  {
    return std::to_string(number);
  }

  QString toPath(const QStringList& pathParts)
  {
    return pathParts.join('/');
  }

  QJsonObject toJsonObject(const QString& string)
  {
    QJsonDocument sd = QJsonDocument::fromJson(string.toUtf8());
    return sd.object();
  }

  QString toString(int number)
  {
    return QString::number(number);
  }

  QString toString(double number)
  {
    return QString::number(number);
  }

  QString toString(const QDate& date)
  {
    return date.toString(dateFormat);
  }

  QRect toRect(const QJsonObject& jsonObject)
  {
    int left = jsonObject["left"].toInt(0);
    int top = jsonObject["top"].toInt(0);
    int width = jsonObject["width"].toInt(0);
    int height = jsonObject["width"].toInt(0);

    return QRect(left, top, width, height);
  }

  QJsonObject toJsonObject(const QRect& rect)
  {
    QJsonObject jsonObject;
    jsonObject["left"] = rect.left();
    jsonObject["top"] = rect.top();
    jsonObject["width"] = rect.width();
    jsonObject["height"] = rect.height();

    return jsonObject;
  }

  QJsonObject configFileToJsonObject(const QString& programName, const QString& fileName)
  {
    QString fileContent = File(Path::configurationFile(programName, fileName)).toString();
    return toJsonObject(fileContent);
  }

  void jsonObjectToConfigFile(const QJsonObject& jsonObject, const QString& programName, const QString& fileName)
  {
    // TODO check if directory exists...
    QFile file(Path::configurationFile(programName, fileName));

    if (!file.open(QIODevice::WriteOnly))
    {
      qWarning("Couldn't open save file.");
    }

    QJsonDocument jsonDocument(jsonObject);

    file.write(jsonDocument.toJson());
    file.close();
  }

  QString toHtml(const QString& sml, bool createInfrastructure)
  {
    SmlConverter smlConverter;
    return smlConverter.toHtml(sml, createInfrastructure);
  }

  QString toString(const QStringList& stringList, const QChar& seperator)
  {
    return stringList.join(seperator);
  }

  QStringList toStringList(const QString& string, const QChar& seperator, QString::SplitBehavior splitBehaviour)
  {
    return string.split('\n', splitBehaviour);
  }

  QString toString(const QDateTime& dateTime)
  {
    return dateTime.toString(dateTimeFormat);
  }

  QDateTime toDateTime(const QString& dateTime)
  {
    return QDateTime::fromString(dateTime, dateTimeFormat);
  }
}
