#include <QDebug>

#include "QStringEx.h"

namespace QStringEx
{
  uint16 removeTrailingSigns(QString& string, const QChar& trailingSign)
  {
    uint16 counter = 0;

    while (!string.isEmpty() && string.endsWith(trailingSign))
    {
      counter++;
      string.remove(string.size() - 1, 1);
    }

    return counter;
  }

  uint16 removeLeadingSigns(QString& string, const QChar& leadingSign)
  {
    uint16 counter = 0;

    while (!string.isEmpty() && string.startsWith(leadingSign))
    {
      counter++;
      string.remove(0, 1);
    }

    return counter;
  }

  void addLeadingSigns(QString& string, const QChar& leadingSign, uint16 nLeadingSigns)
  {
    QString leadingSigns(nLeadingSigns, leadingSign);
    string.prepend(leadingSigns);
  }

  uint16 removeTrailingSpaces(QString& string)
  {
    return removeTrailingSigns(string, ' ');
  }

  uint16 removeLeadingSpaces(QString& string)
  {
    return removeLeadingSigns(string, ' ');
  }

  void addLeadingSpaces(QString& string, uint16 nLeadingSpaces)
  {
    addLeadingSigns(string, ' ', nLeadingSpaces);
  }

  QChar peekPrevious(const QString& string, int position, unsigned int distance)
  {
    for (unsigned int i = 0; i < distance; ++i)
    {
      if (!positionValid(string, --position))
      {
        return QChar('\0');
      }
    }

    return string[position];
  }

  QChar peekNext(const QString& string, int position, unsigned int distance)
  {
    for (unsigned int i = 0; i < distance; ++i)
    {
      if (!positionValid(string, ++position))
      {
        return QChar('\0');
      }
    }

    return string[position];
  }

  QChar SHARED_API peekPreviousNonWhitespace(const QString& string, int position, unsigned int distance)
  {
    QChar ch = '\0';

    for (unsigned int i = 0; i < distance; ++i)
    {
      --position;

      while (positionValid(string, position) && isSpace(string, position))
      {
        --position;
      }
    }

    if (positionValid(string, position))
    {
      ch = string[position];
    }

    return ch;
  }

  QChar SHARED_API peekNextNonWhitespace(const QString& string, int position, unsigned int distance)
  {
    QChar ch = '\0';

    for (unsigned int i = 0; i < distance; ++i)
    {
      ++position;

      while (positionValid(string, position) && isSpace(string, position))
      {
        ++position;
      }
    }

    if (positionValid(string, position))
    {
      ch = string[position];
    }

    return ch;
  }

  bool isSurrounded(const QString& string, int position, const QChar& surroundingChar)
  {
    return (peekNext(string, position) == surroundingChar && peekPrevious(string, position) == surroundingChar);
  }

  bool SHARED_API positionValid(const QString& string, int position)
  {
    return (position >= 0 && position < string.size());
  }

  bool SHARED_API isSpace(const QString& string, int position)
  {
    if (!positionValid(string, position))
    {
      return false;
    }

    return (string[position] == ' ' || string[position] == '\t' || string[position] == '\n' || string[position] == '\r' || string[position] == '\v');
  }

  QString SHARED_API lowercaseFirstLetter(const QString& string)
  {
    QString copy = string;

    if (string.length() < 1)
    {
      return string;
    }

    copy[0] = copy[0].toLower();
    return copy;
  }
}