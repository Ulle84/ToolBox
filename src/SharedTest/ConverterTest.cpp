// created on 2017-03-30 by Ulrich Belitz

#include <QtTest>

#include "Converter.h"
#include "Test.h"
#include "ConverterTest.h"
#include "UInt.h"

void ConverterTest::toHtml()
{
  QString testName = "toHtml";

  QString input;
  QString output;

  for (int i = 1; i <= 11; ++i)
  {
    qDebug() << "#" << i;

    QString number = UInt(i).toString(2);

    QVERIFY(Test::loadFile(m_module, m_category, testName, QString("%1_input.txt").arg(number), input));
    QVERIFY(Test::loadFile(m_module, m_category, testName, QString("%1_output.txt").arg(number), output));

    QCOMPARE(Converter::toHtml(input, false), output);
  }
}
