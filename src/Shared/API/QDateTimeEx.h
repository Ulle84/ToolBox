// created on 2017-01-25 by Ulrich Belitz

#ifndef QDATETIMEEX_H
#define QDATETIMEEX_H

#include <QString>
#include <QDateTime>

#include "SharedAPI.h"

namespace QDateTimeEx
{
	QString SHARED_API currentDateTime();

  QString SHARED_API toString(const QDateTime& dateTime);
  QDateTime SHARED_API fromString(const QString& dateTime);

  const QString dateTimeFormat = "yyyy-MM-dd hh:mm:ss";
}

#endif