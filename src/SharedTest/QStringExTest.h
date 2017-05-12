// created on 2017-03-01 by Ulrich Belitz

#ifndef QSTRINGEXTEST_H
#define QSTRINGEXTEST_H

#include <QObject>

class QStringExTest : public QObject
{
    Q_OBJECT

  private slots:
    void peekNext();
    void peekPrevious();
    void peekNextWithDistance();
    void peekPreviousWithDistance();
    void positionValid();
    void peekNextNonWhitespace();
    void peekPreviousNonWhitespace();
    void peekNextNonWhitespaceWithDistance();
    void peekPreviousNonWhitespaceWithDistance();
    void lowercaseFirstLetter();
    void replace();
};

#endif