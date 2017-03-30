// created on 2017-03-30 by Ulrich Belitz

#include <QString>
#include <QtTest>

#include "Path.h"
#include "File.h"
#include "Text.h"
#include "TextTest.h"

void TextTest::indentColumns1()
{
  QString testName = "indentColumns1";

  QStringList input = File::fileToStringList(testFile(testName, "input.txt"));
  QStringList output = File::fileToStringList(testFile(testName, "output.txt"));

  QVERIFY(input.size() != 0);
  QVERIFY(output.size() != 0);

  QVERIFY(Text::indentColumns(input, "<<<<<<"));

  //Text::indentColumns(input, "<<<<<<");
  //File::stringListToFile(input, testFile(testName, "outputCmp.txt"));

  QCOMPARE(input, output);
}
QString TextTest::testFile(const QString& testName, const QString& fileName)
{
  return Path::testFile("Shared", "Text", testName, fileName);
}
