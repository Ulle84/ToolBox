// created on 2017-03-29 by Ulrich Belitz

#ifndef TEXT_H
#define TEXT_H

#include <QString>
#include <QStringList>

#include "SharedAPI.h"

namespace Text
{
  // TODO method with string
  //bool SHARED_API indentColumns(QString& input, const QString& alignments, QChar seperator = ' ');
  bool SHARED_API indentColumns(QStringList& input, const QString& alignments, QChar seperator = ' ');
};

#endif