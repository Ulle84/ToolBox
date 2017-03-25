// created on 2017-03-25 by Ulrich Belitz

#include <QString>
#include <QtTest>

#include "Path.h"
#include "PathTest.h"



void PathTest::directory()
{
	QCOMPARE(Path::directory("C:/hello/world/test.txt"), QString("C:/hello/world"));
}

void PathTest::fileName()
{
	QCOMPARE(Path::fileName("C:/hello/world/test.txt"), QString("test.txt"));
}

void PathTest::fileNameWithoutExtension()
{
	QCOMPARE(Path::fileNameWithoutExtension("C:/hello/world/test.txt"), QString("test"));
}

void PathTest::fileNameExtension()
{
	QCOMPARE(Path::fileNameExtension("C:/hello/world/test.txt"), QString("txt"));
}
