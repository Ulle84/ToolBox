// created on 2016-12-15 by Ulrich Belitz

#ifndef CONVERTER_H
#define CONVERTER_H

#include "SharedAPI.h"

namespace Converter
{
  std::string SHARED_API toString(int number);
  QJsonObject SHARED_API toJson(const QString& string);
  QString SHARED_API toQString(int number);
}

#endif