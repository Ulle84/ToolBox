// created on 2017-03-01 by Ulrich Belitz

#include <QString>
#include <QtTest>

#include "File.h"
#include "FileTest.h"

void FileTest::directory()
{
  QString test = "C:/hello/world.png";
  QCOMPARE(File::directory(test), QString("C:/hello"));

  test = "C:\\hello\\world.png";
  QCOMPARE(File::directory(test), QString("C:\\hello"));
}
