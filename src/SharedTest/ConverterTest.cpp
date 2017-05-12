// created on 2017-03-30 by Ulrich Belitz

#include <QString>
#include <QtTest>

#include "Path.h"
#include "File.h"
#include "Converter.h"

#include "ConverterTest.h"

// TODO create TestHelper

void ConverterTest::toHtml01()
{
  QString testName = "toHtml01";

  QStringList input = File::fileToStringList(testFile(testName, "input.txt"));
  QStringList output = File::fileToStringList(testFile(testName, "output.txt"));

  QVERIFY(input.size() != 0);
  QVERIFY(output.size() != 0);

  QVERIFY();

  QCOMPARE(input, output);
}

QString ConverterTest::testFile(const QString& testName, const QString& fileName)
{
  return Path::testFile("Shared", "Text", testName, fileName);
}
