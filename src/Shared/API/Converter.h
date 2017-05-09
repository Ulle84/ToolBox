// created on 2016-12-15 by Ulrich Belitz

#ifndef CONVERTER_H
#define CONVERTER_H

#include <QRect>
#include <QJsonObject>

#include "SharedAPI.h"

// TODO create Test for Converter!!!
namespace Converter
{
  // TODO unifiy interface only toBlub methods - if arguments are not unique -> introduce enum to indiciate type of argument
  // TODO check all other helpers, if some functions can be moved here

  std::string SHARED_API toString(int number);
  QJsonObject SHARED_API toJsonObject(const QString& string);
  QString SHARED_API toQString(int number);

  // TODO test the two methods below
  QRect SHARED_API toRect(const QJsonObject& jsonObject);
  QJsonObject SHARED_API toJsonObject(const QRect& rect);

  QJsonObject SHARED_API configFileToJsonObject(const QString& programName, const QString& fileName);
  void SHARED_API jsonObjectToConfigFile(const QJsonObject& jsonObject, const QString& programName, const QString& fileName);

  QString SHARED_API toPath(const QStringList& pathParts);

  QString SHARED_API toHtml(const QString& sml);
}

#endif