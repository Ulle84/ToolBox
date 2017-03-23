// created on 2017-03-10 by Ulrich Belitz

#include <QtTest>

#include "RingBuffer.h"
#include "RingBufferTest.h"

void RingBufferTest::singleAccess()
{
  int size = 20;

  RingBuffer<int> ringBuffer(size);
  ringBuffer.setTimeout(10);

  QCOMPARE(ringBuffer.size(), size);

  // run twice to see if "index-overflow" is handled properly
  for (int j = 0; j < 2; ++j)
  {
    // fill the ring buffer
    for (int i = 0; i < size; ++i)
    {
      QVERIFY(ringBuffer.write(i));
    }

    // ring buffer is already filled
    QVERIFY(!ringBuffer.write(0));

    //read the ring buffer
    int readData = 0;
    for (int i = 0; i < size; ++i)
    {
      QVERIFY(ringBuffer.read(readData));
      QCOMPARE(readData, i);
    }

    // no more to read
    QVERIFY(!ringBuffer.read(readData));
  }
}

void RingBufferTest::vectorAccess()
{
  int vecSize = 10;
  int n = 3;
  int size = n * vecSize;

  RingBuffer<int> ringBuffer(size);
  ringBuffer.setTimeout(10);

  std::vector<int> vec;
  vec.resize(vecSize);

  for (int i = 0; i < vecSize; ++i)
  {
    vec[i] = i;
  }

  QCOMPARE(ringBuffer.size(), size);

  // run twice to see if "index-overflow" is handled properly
  for (int j = 0; j < 2; ++j)
  {
    // fill the ring buffer
    for (int i = 0; i < n; ++i)
    {
      QVERIFY(ringBuffer.write(vec));
    }

    // ring buffer is already filled
    QVERIFY(!ringBuffer.write(0));

    //read the ring buffer
    std::vector<int> readData;
    readData.resize(vecSize);
    for (int i = 0; i < n; ++i)
    {
      QVERIFY(ringBuffer.read(readData));
      for (int k = 0; k < vecSize; ++k)
      {
        QCOMPARE(readData[k], k);
      }      
    }
    
    // no more to read
    QVERIFY(!ringBuffer.read(readData));
  }
}

void RingBufferTest::directAccess()
{
  int size = 20;

  RingBuffer<int> ringBuffer(size);
  ringBuffer.setTimeout(10);

  QCOMPARE(ringBuffer.size(), size);

  // run twice to see if "index-overflow" is handled properly
  for (int j = 0; j < 2; ++j)
  {
    // try to acquire too much space
    QVERIFY(!ringBuffer.writePossible(size + 1));
    
    // acquire as much space as possible and write data
    QVERIFY(ringBuffer.writePossible(size));

    for (int i = 0; i < size; ++i)
    {
      *ringBuffer.write() = i;
    }

    // try to read to early
    QVERIFY(!ringBuffer.readPossible(1));

    ringBuffer.writeDone(size);

    // readout data
    QVERIFY(ringBuffer.readPossible(size));

    for (int i = 0; i < size; ++i)
    {
      QCOMPARE(*ringBuffer.read(), i);
    }

    ringBuffer.readDone(size);
  }
}

void RingBufferTest::reset()
{
  int size = 20;

  RingBuffer<int> ringBuffer(size);
  ringBuffer.setTimeout(10);

  QCOMPARE(ringBuffer.size(), size);

  // fill the ring buffer
  for (int i = 0; i < size; ++i)
  {
    QVERIFY(ringBuffer.write(i));
  }

  // ring buffer is already filled
  QVERIFY(!ringBuffer.write(0));

  ringBuffer.reset();

  // try to read
  int readData = 0;
  QVERIFY(!ringBuffer.read(readData));

  // run twice to see if "index-overflow" is handled properly
  for (int j = 0; j < 2; ++j)
  {
    // fill the ring buffer
    for (int i = 0; i < size; ++i)
    {
      QVERIFY(ringBuffer.write(i));
    }

    // ring buffer is already filled
    QVERIFY(!ringBuffer.write(0));

    //read the ring buffer    
    for (int i = 0; i < size; ++i)
    {
      QVERIFY(ringBuffer.read(readData));
      QCOMPARE(readData, i);
    }

    // no more to read
    QVERIFY(!ringBuffer.read(readData));
  }
}
