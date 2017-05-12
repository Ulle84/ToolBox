// created on 2017-03-01 by Ulrich Belitz

#include <QString>
#include <QtTest>
#include <QDebug>

#include "CppHelper.h"
#include "CppHelperTest.h"
#include "Path.h"
#include "FileOld.h"

/*
these two functions must be implemented, if required:
void initTestCase();
void cleanupTestCase();
*/

QString CppHelperTest::testFile(const QString& testName, const QString& fileName)
{
  return Path::testFile("Shared", "CppHelper", testName, fileName);
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