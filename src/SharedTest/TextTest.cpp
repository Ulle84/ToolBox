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

  QStringList input = File(testFile(testName, "input.cpp")).toStringList();
  QStringList output = File(testFile(testName, "output.cpp")).toStringList();

  QVERIFY(input.size() != 0);
  QVERIFY(output.size() != 0);

  QVERIFY(Text::indentColumns(input, "<<<<<<"));

  QCOMPARE(input, output);
}

void TextTest::indentColumns2()
{
  QString testName = "indentColumns2";

  QStringList input = File(testFile(testName, "input.cpp")).toStringList();
  QStringList output = File(testFile(testName, "output.cpp")).toStringList();

  QVERIFY(input.size() != 0);
  QVERIFY(output.size() != 0);

  QVERIFY(Text::indentColumns(input, ">>>>"));

  QCOMPARE(input, output);
}

QString TextTest::testFile(const QString& testName, const QString& fileName)
{
  return Path::testFile("Shared", "Text", testName, fileName);
}
