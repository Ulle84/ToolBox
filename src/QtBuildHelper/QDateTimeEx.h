// created on 2017-01-25 by Ulrich Belitz

#ifndef QDATETIMEEX_H
#define QDATETIMEEX_H

#include <QString>
#include <QDateTime>

namespace QDateTimeEx
{
  QString toString(const QDateTime& dateTime);

  const QString dateTimeFormat = "yyyy-MM-dd hh:mm:ss";
}

#endif