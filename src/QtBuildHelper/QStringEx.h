// created on 2016-12-14

#ifndef QSTRINGEX_H
#define QSTRINGEX_H

#include <QString>
#include <QChar>

#include "CustomTypes.h"

namespace QStringEx
{
  uint16 removeTrailingSigns(QString& string, const QChar& trailingSign);
  uint16 removeLeadingSigns(QString& string, const QChar& leadingSign);
  void addLeadingSigns(QString& string, const QChar& leadingSign, uint16 nLeadingSigns);

  uint16 removeTrailingSpaces(QString& string);
  uint16 removeLeadingSpaces(QString& string);
  void addLeadingSpaces(QString& string, uint16 nLeadingSpaces);

  QChar peekPrevious(const QString& string, int position, uint distance = 1);
  QChar peekNext(const QString& string, int position, uint distance = 1);

  QChar peekPreviousNonWhitespace(const QString& string, int position, uint distance = 1);
  QChar peekNextNonWhitespace(const QString& string, int position, uint distance = 1);

  bool isSurrounded(const QString& string, int position, const QChar& surroundingChar);

  bool positionValid(const QString& string, int position);
  bool isSpace(const QString& string, int position);

  QString lowercaseFirstLetter(const QString& string);

  QString replace(const QString& input, const QString& before, const QString& after, uint startPos = 0);
}

#endif