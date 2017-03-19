// created on 2016-12-15 by Ulrich Belitz

#ifndef QCONVERTER_H
#define QCONVERTER_H

#include <QString>
#include <QStringList>

#include "SharedAPI.h"

namespace QConverter
{
  QString SHARED_API toString(const QStringList& stringList, const QChar& seperator = '\n');

  QStringList SHARED_API toStringList(const QString& string, const QChar& seperator = '\n', QString::SplitBehavior splitBehaviour = QString::KeepEmptyParts);
}

#endif