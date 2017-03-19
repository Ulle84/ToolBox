// created on 2016-12-14

#ifndef INTHELPER_H
#define INTHELPER_H

#include <string>

#include "CustomTypes.h"
#include "SharedAPI.h"

namespace IntHelper
{
  std::string SHARED_API fillString(uint32 smallerNumber, uint32 biggerNumber, char fillCharacter = ' ');
  uint8 SHARED_API numberOfDigits(uint32 number);
}

#endif