// created on 2017-03-01 by Ulrich Belitz

#include <QString>
#include <QtTest>

#include "Path.h"
#include "File.h"
#include "FileTest.h"

void FileTest::directory()
{
  QString test = "C:/hello/world.png";
  QCOMPARE(File::directory(test), QString("C:/hello"));

  test = "C:\\hello\\world.png";
  QCOMPARE(File::directory(test), QString("C:\\hello"));
}

void FileTest::merge()
{
  QString testName = "merge";

  QStringList output = File::fileToStringList(testFile(testName, "output.txt"));

  QVERIFY(output.size() != 0);

  QStringList files;
  files << testFile(testName, "input01.txt");
  files << testFile(testName, "input02.txt");
  files << testFile(testName, "input03.txt");

  QStringList combined = File::merge(files);

  QCOMPARE(combined, output);
}
QString FileTest::testFile(const QString& testName, const QString& fileName)
{
  return Path::testFile("Shared", "File", testName, fileName);
}
