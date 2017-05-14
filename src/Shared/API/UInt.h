#ifndef UINT_H
#define UINT_H

#include <QString>

#include "CustomTypes.h"
#include "SharedAPI.h"

class SHARED_API UInt
{
  public:
    UInt(uint value);

    QString toString(uint8 minDigits, QChar leadingSign = '0');
    uint8 nDigits();

  private:
    uint m_value;
};

#endif