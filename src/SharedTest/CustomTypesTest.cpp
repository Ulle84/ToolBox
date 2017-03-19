// created on 2017-03-03 by Ulrich Belitz

#include <QtTest>

#include "CustomTypesTest.h"
#include "CustomTypes.h"

void CustomTypesTest::testByteSizes()
{
  QCOMPARE(sizeof(int8), unsigned __int64(1));
  QCOMPARE(sizeof(int16), unsigned __int64(2));
  QCOMPARE(sizeof(int32), unsigned __int64(4));
  QCOMPARE(sizeof(int64), unsigned __int64(8));

  QCOMPARE(sizeof(uint8), unsigned __int64(1));
  QCOMPARE(sizeof(uint16), unsigned __int64(2));
  QCOMPARE(sizeof(uint32), unsigned __int64(4));
  QCOMPARE(sizeof(uint64), unsigned __int64(8));
}
