// created on 2017-03-30 by Ulrich Belitz

#include <QtTest>

#include "Converter.h"
#include "Test.h"
#include "ConverterTest.h"

void ConverterTest::toHtml()
{
  QString testName = "toHtml";

  QString input;
  QString output;

  QVERIFY(Test::loadFile(m_module, m_category, testName, "input01.txt", input));
  QVERIFY(Test::loadFile(m_module, m_category, testName, "output01.txt", output));

  QCOMPARE(Converter::toHtml(input, false), output);
}
