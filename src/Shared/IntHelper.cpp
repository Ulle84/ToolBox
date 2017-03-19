#include "IntHelper.h"

namespace IntHelper
{
  std::string fillString(uint32 smallerNumber, uint32 biggerNumber, char fillCharacter)
  {
    int8 diff = numberOfDigits(biggerNumber) - numberOfDigits(smallerNumber);

    if (diff > 0)
    {
      return std::string(diff, fillCharacter);
    }
    else
    {
      return std::string();
    }
  }

  uint8 numberOfDigits(uint32 number)
  {
    uint8 nDigits = 1;

    while (number >= 10)
    {
      number /= 10;
      nDigits++;
    }

    return nDigits;
  }
}