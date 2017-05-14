#include "UInt.h"

UInt::UInt(uint value) :
  m_value(value)
{
}

QString UInt::toString(uint8 minDigits, QChar leadingSign)
{
  QString string = QString::number(m_value);

  int8 diff = minDigits - nDigits();

  if (diff > 0)
  {
    QString leading = QString(diff, leadingSign);
    string.prepend(leading);
  }

  return string;
}

uint8 UInt::nDigits()
{
  uint8 result = 1;

  uint number = m_value;

  while (number >= 10)
  {
    number /= 10;
    result++;
  }

  return result;
}
