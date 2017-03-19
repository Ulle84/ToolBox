// created on 2017-03-10 by Ulrich Belitz

#ifndef RINGBUFFERTEST_H
#define RINGBUFFERTEST_H

#include <QObject>

class RingBufferTest : public QObject
{
    Q_OBJECT

  private slots:
    void singleAccess();
    void vectorAccess();
    void directAccess();
};

#endif