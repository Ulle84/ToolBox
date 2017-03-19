// created on 2016-12-15 by Ulrich Belitz

#include "QConverter.h"

namespace QConverter
{

  QString toString(const QStringList& stringList, const QChar& seperator)
  {
    return stringList.join(seperator);
  }


  QStringList toStringList(const QString& string, const QChar& seperator, QString::SplitBehavior splitBehaviour)
  {
    return string.split('\n', splitBehaviour);
  }

}
