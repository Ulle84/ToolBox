// created on 2017-03-01 by Ulrich Belitz

#include <QString>
#include <QtTest>
#include <QDebug>

#include "CppHelper.h"
#include "CppHelperTest.h"
#include "Path.h"
#include "File.h"

/*
these two functions must be implemented, if required:
void initTestCase();
void cleanupTestCase();
*/

QString CppHelperTest::testFile(const QString& testName, const QString& fileName)
{
  return Path::testFile("Shared", "CppHelper", testName, fileName);
}

void CppHelperTest::clean01()
{
  QString testName = "Clean01";

  QString input = File(testFile(testName, "input.cpp")).toString();
  QString output = File(testFile(testName, "output.cpp")).toString();

  QVERIFY(input.size() != 0);
  QVERIFY(output.size() != 0);

  CppHelper cppHelper;
  cppHelper.clean(input);

  QCOMPARE(input, output);
}

void CppHelperTest::clean02()
{
  QString testName = "Clean02";

  QString input = File(testFile(testName, "input.cpp")).toString();
  QString output = File(testFile(testName, "output.cpp")).toString();

  QVERIFY(input.size() != 0);
  QVERIFY(output.size() != 0);

  CppHelper cppHelper;
  cppHelper.clean(input);

  QCOMPARE(input, output);
}

void CppHelperTest::lineComments()
{
  QString testName = "LineComments";

  QString input = File(testFile(testName, "input.txt")).toString();
  QString original = input;
  QString output = File(testFile(testName, "output.txt")).toString();
  QStringList expectedLineComments = File(testFile(testName, "lineComments.txt")).toStringList();

  CppHelper cppHelper;
  cppHelper.shrinkCommentsAndStrings(input);

  QCOMPARE(input, output);
  QCOMPARE(cppHelper.m_lineComments, expectedLineComments);

  cppHelper.expandCommentsAndStrings(input);

  QCOMPARE(input, original);
}

void CppHelperTest::lineCommentLeadingStar()
{
  QString input = "//*test002";
  QString original = input;
  CppHelper cppHelper;
  cppHelper.shrinkCommentsAndStrings(input);

  QCOMPARE(input, QString("//"));

  QStringList expectedLineComments;
  expectedLineComments << "*test002";

  QCOMPARE(cppHelper.m_lineComments, expectedLineComments);

  cppHelper.expandCommentsAndStrings(input);

  QCOMPARE(input, original);
}

void CppHelperTest::blockComment()
{
  QString input = "/*test003*/";
  QString original = input;
  CppHelper cppHelper;
  cppHelper.shrinkCommentsAndStrings(input);

  QCOMPARE(input, QString("/**/"));

  QStringList expectedBlockComments;
  expectedBlockComments << "test003";

  QCOMPARE(cppHelper.m_blockComments, expectedBlockComments);

  cppHelper.expandCommentsAndStrings(input);

  QCOMPARE(input, original);
}

void CppHelperTest::string()
{
  QString input = "test = \"// 004\"";
  QString original = input;
  CppHelper cppHelper;
  cppHelper.shrinkCommentsAndStrings(input);

  QCOMPARE(input, QString("test = \"\""));

  QStringList expectedStrings;
  expectedStrings << "// 004";

  QCOMPARE(cppHelper.m_strings, expectedStrings);

  cppHelper.expandCommentsAndStrings(input);

  QCOMPARE(input, original);
}

void CppHelperTest::notAString()
{
  QString input = "char a = \'\\\"\'\nchar b = \'\\\"\'";
  QString original = input;
  CppHelper cppHelper;
  cppHelper.shrinkCommentsAndStrings(input);

  QCOMPARE(input, original);

  QStringList expectedStrings;

  QCOMPARE(cppHelper.m_strings, expectedStrings);

  cppHelper.expandCommentsAndStrings(input);

  QCOMPARE(input, original);
}

void CppHelperTest::removeSvnId()
{
  QString testName = "RemoveSvnId";

  QString input = File(testFile(testName, "input.cpp")).toString();
  QString output = File(testFile(testName, "output.cpp")).toString();

  QVERIFY(input.size() != 0);
  QVERIFY(output.size() != 0);

  CppHelper cppHelper;
  cppHelper.removeSvnId(input);

  QCOMPARE(input, output);
}
