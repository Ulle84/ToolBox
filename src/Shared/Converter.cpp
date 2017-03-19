// created on 2016-12-15 by Ulrich Belitz

#include <QJsonDocument>
#include <QString>
#include <QJsonObject>

#include "Converter.h"

namespace Converter
{

  std::string toString(int number)
  {
    return std::to_string(number);
  }

  QJsonObject SHARED_API toJson(const QString& string)
  {
    QJsonDocument sd = QJsonDocument::fromJson(string.toUtf8());
    return sd.object();
  }

  QString SHARED_API toQString(int number)
  {
    return QString::number(number);
  }

}
