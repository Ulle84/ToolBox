#include <QtTest>

#include "UInt.h"
#include "UIntTest.h"

void UIntTest::toString()
{
  UInt value(12);

  QCOMPARE(UInt(12).toString(1), QString("12"));
  QCOMPARE(UInt(12).toString(1), QString("12"));
  QCOMPARE(UInt(12).toString(3), QString("012"));
  QCOMPARE(UInt(12).toString(3, ' '), QString(" 12"));
}

void UIntTest::nDigits()
{
  QCOMPARE(UInt(12).nDigits(), (uint8)2);
  QCOMPARE(UInt(0).nDigits(), (uint8)1);
  QCOMPARE(UInt(123).nDigits(), (uint8)3);
  QCOMPARE(UInt(245235).nDigits(), (uint8)6);
}
