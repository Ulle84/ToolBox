// created on 2016-12-15 by Ulrich Belitz

#include <QJsonDocument>
#include <QString>
#include <QJsonObject>
#include <QFile>

#include "Converter.h"
#include "File.h"
#include "Path.h"

namespace Converter
{
  std::string toString(int number)
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

  QString toQString(int number)
  {
    return QString::number(number);
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

  QJsonObject SHARED_API configFileToJsonObject(const QString& programName, const QString& fileName)
  {
    QString fileContent = File::fileToString(Path::configurationFile(programName, fileName));
    return toJsonObject(fileContent);
  }

  void SHARED_API jsonObjectToConfigFile(const QJsonObject& jsonObject, const QString& programName, const QString& fileName)
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
}
