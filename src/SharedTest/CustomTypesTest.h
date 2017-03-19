// created on 2017-03-03 by Ulrich Belitz

#ifndef CUSTOMTYPESTEST_H
#define CUSTOMTYPESTEST_H

#include <QObject>

class CustomTypesTest : public QObject
{
    Q_OBJECT

  private slots:
    void testByteSizes();
};

#endif