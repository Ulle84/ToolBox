// created on 2017-03-01 by Ulrich Belitz

#include <QString>
#include <QtTest>

#include "Path.h"
#include "File.h"
#include "FileTest.h"

void FileTest::directory()
{
  QString test = "C:/hello/world.png";
  QCOMPARE(File(test).directory(), QString("C:/hello"));

  test = "C:\\hello\\world.png";
  QCOMPARE(File(test).directory(), QString("C:\\hello"));
}

QString FileTest::testFile(const QString& testName, const QString& fileName)
{
  return Path::testFile("Shared", "File", testName, fileName);
}
