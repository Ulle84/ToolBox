#ifndef UINTTEST_H
#define UINTTEST_H

#include <QObject>

class UIntTest : public QObject
{
    Q_OBJECT

  private slots:
    void toString();
    void nDigits();
};

#endif