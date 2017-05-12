// created on 2017-03-25 by Ulrich Belitz

#ifndef PATHTEST_H
#define PATHTEST_H

#include <QObject>

class PathTest : public QObject
{
    Q_OBJECT

  private slots:
    void directory();
    void fileName();
    void fileNameWithoutExtension();
    void fileNameExtension();
};

#endif