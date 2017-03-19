// created on 2017-03-01 by Ulrich Belitz

#include <QString>
#include <QtTest>

#include "QStringEx.h"
#include "QStringExTest.h"

void QStringExTest::peekNext()
{
  QString string = "0123456789";

  QCOMPARE(QStringEx::peekNext(string, -1), QChar('0'));
  QCOMPARE(QStringEx::peekNext(string, 10), QChar('\0'));
  QCOMPARE(QStringEx::peekNext(string, 0), QChar('1'));
}

void QStringExTest::peekPrevious()
{
  QString string = "0123456789";

  QCOMPARE(QStringEx::peekPrevious(string, 1), QChar('0'));
  QCOMPARE(QStringEx::peekPrevious(string, 0), QChar('\0'));
  QCOMPARE(QStringEx::peekPrevious(string, 10), QChar('9'));
  QCOMPARE(QStringEx::peekPrevious(string, 11), QChar('\0'));
}

void QStringExTest::peekNextWithDistance()
{
  QString string = "0123456789";

  QCOMPARE(QStringEx::peekNext(string, 0, 0), QChar('0'));
  QCOMPARE(QStringEx::peekNext(string, 0, 1), QChar('1'));
  QCOMPARE(QStringEx::peekNext(string, 0, 2), QChar('2'));
  QCOMPARE(QStringEx::peekNext(string, 0, 3), QChar('3'));
  QCOMPARE(QStringEx::peekNext(string, 0, 10), QChar('\0'));
}

void QStringExTest::peekPreviousWithDistance()
{
  QString string = "0123456789";

  QCOMPARE(QStringEx::peekPrevious(string, 9, 0), QChar('9'));
  QCOMPARE(QStringEx::peekPrevious(string, 9, 1), QChar('8'));
  QCOMPARE(QStringEx::peekPrevious(string, 9, 2), QChar('7'));
  QCOMPARE(QStringEx::peekPrevious(string, 9, 3), QChar('6'));
  QCOMPARE(QStringEx::peekPrevious(string, 9, 10), QChar('\0'));
}

void QStringExTest::positionValid()
{
  QString test = "hello";
  QVERIFY(!QStringEx::positionValid(test, -1));

  for (int i = 0; i < test.size(); ++i)
    QVERIFY(QStringEx::positionValid(test, i));
  
  QVERIFY(!QStringEx::positionValid(test, 5));
}

void QStringExTest::peekNextNonWhitespace()
{
  QString test = "h ello\t\nworld";

  QCOMPARE(QStringEx::peekNextNonWhitespace(test, -1), QChar('h'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 0), QChar('e'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 1), QChar('e'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 5), QChar('w'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 6), QChar('w'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 7), QChar('w'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 12), QChar('\0'));
}

void QStringExTest::peekPreviousNonWhitespace()
{
  QString test = "h ello\t\nworld";

  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 0), QChar('\0'));
  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 1), QChar('h'));
  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 2), QChar('h'));
  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 6), QChar('o'));
  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 7), QChar('o'));
  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 8), QChar('o'));
  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 13), QChar('d'));
}

void QStringExTest::peekNextNonWhitespaceWithDistance()
{
  QString test = "h e l l o";

  QCOMPARE(QStringEx::peekNextNonWhitespace(test, -1, 1), QChar('h'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 0, 0), QChar('h'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 0, 1), QChar('e'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 0, 2), QChar('l'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 0, 3), QChar('l'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 0, 4), QChar('o'));
  QCOMPARE(QStringEx::peekNextNonWhitespace(test, 0, 5), QChar('\0'));
}

void QStringExTest::peekPreviousNonWhitespaceWithDistance()
{
  QString test = "h e l l o";

  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 9, 1), QChar('o'));
  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 9, 2), QChar('l'));
  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 9, 3), QChar('l'));
  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 9, 4), QChar('e'));
  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 9, 5), QChar('h'));
  QCOMPARE(QStringEx::peekPreviousNonWhitespace(test, 9, 6), QChar('\0'));
}

void QStringExTest::lowercaseFirstLetter()
{
  QString test = "Hello";

  QString firstLetterLowercased = QStringEx::lowercaseFirstLetter(test);

  QCOMPARE(firstLetterLowercased, QString("hello"));
}
