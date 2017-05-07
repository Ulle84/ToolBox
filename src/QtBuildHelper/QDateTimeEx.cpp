// created on 2017-01-25 by Ulrich Belitz

#include "QDateTimeEx.h"

namespace QDateTimeEx
{
  QString toString(const QDateTime& dateTime)
  {
    return dateTime.toString(dateTimeFormat);
  }
}
