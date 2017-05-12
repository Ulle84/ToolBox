// created on 2016-12-15 by Ulrich Belitz

#ifndef CONVERTER_H
#define CONVERTER_H

#include <QRect>
#include <QJsonObject>
#include <QDateTime>

#include "SharedAPI.h"

namespace Converter
{
  QString SHARED_API toString(int number);
  QString SHARED_API toString(double number);
  QString SHARED_API toString(const QStringList& stringList, const QChar& seperator = '\n');
  QString SHARED_API toString(const QDateTime& dateTime);
  QString SHARED_API toString(const QDate& date);
  
  QDateTime SHARED_API toDateTime(const QString& dateTime);

  QStringList SHARED_API toStringList(const QString& string, const QChar& seperator = '\n', QString::SplitBehavior splitBehaviour = QString::KeepEmptyParts);

  std::string SHARED_API toStdString(int number);

  QJsonObject SHARED_API toJsonObject(const QString& string);
  QJsonObject SHARED_API toJsonObject(const QRect& rect);

  QRect SHARED_API toRect(const QJsonObject& jsonObject);

  QString SHARED_API toPath(const QStringList& pathParts);

  QString SHARED_API toHtml(const QString& sml, bool createInfrastructure = true);

  QJsonObject SHARED_API configFileToJsonObject(const QString& programName, const QString& fileName);
  void SHARED_API jsonObjectToConfigFile(const QJsonObject& jsonObject, const QString& programName, const QString& fileName);

  static const QString dateFormat = "yyyy-MM-dd";
  static const QString timeFormat = "hh:mm:ss";
  static const QString dateTimeFormat = "yyyy-MM-dd hh:mm:ss";
}

#endif