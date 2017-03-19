// created on 2016-12-15 by Ulrich Belitz

#include "CustomTypes.h"
#include "Machine.h"

namespace Machine
{
  bool hasLittleEndian()
  {
    union
    {
      uint32 i;
      struct
      {
        uint8 c0;
        uint8 c1;
        uint8 c2;
        uint8 c3;
      } si;
    } t;
    t.i = 0x12345678;

    return (0x12 != t.si.c0);
  }
}
