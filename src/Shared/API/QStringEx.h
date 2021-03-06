// created on 2016-12-14

#ifndef QSTRINGEX_H
#define QSTRINGEX_H

#include <QString>
#include <QChar>

#include "CustomTypes.h"
#include "SharedAPI.h"

namespace QStringEx
{
  uint16 SHARED_API removeTrailingSigns(QString& string, const QChar& trailingSign);
  uint16 SHARED_API removeLeadingSigns(QString& string, const QChar& leadingSign);
  void SHARED_API addLeadingSigns(QString& string, const QChar& leadingSign, uint16 nLeadingSigns);

  uint16 SHARED_API removeTrailingSpaces(QString& string);
  uint16 SHARED_API removeLeadingSpaces(QString& string);
  void SHARED_API addLeadingSpaces(QString& string, uint16 nLeadingSpaces);

  QChar SHARED_API peekPrevious(const QString& string, int position, uint distance = 1);
  QChar SHARED_API peekNext(const QString& string, int position, uint distance = 1);

  QChar SHARED_API peekPreviousNonWhitespace(const QString& string, int position, uint distance = 1);
  QChar SHARED_API peekNextNonWhitespace(const QString& string, int position, uint distance = 1);

  bool SHARED_API isSurrounded(const QString& string, int position, const QChar& surroundingChar);

  bool SHARED_API positionValid(const QString& string, int position);
  bool SHARED_API isSpace(const QString& string, int position);

  QString SHARED_API lowercaseFirstLetter(const QString& string);

  QString SHARED_API replace(const QString& input, const QString& before, const QString& after, uint startPos = 0);

  QString SHARED_API leadingSpaces(const QString& input);
  int SHARED_API nLeadingSpaces(const QString& input);

  bool SHARED_API startsWith(const QString& input, const QString& begin, bool ignoreWhitespacesAtBegin);

  bool SHARED_API isInsideLeadingSpace(const QString& input, int index);
}

#endif