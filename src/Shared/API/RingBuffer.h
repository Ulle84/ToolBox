// created on 2017-03-10 by Ulrich Belitz

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <vector>

#include <QSemaphore>

template<typename T>
class RingBuffer
{
  public:
    RingBuffer(int size);
    ~RingBuffer();

    // the methods read and write are suitable for primitive data types, such as bool, int, double etc.
    bool write(T value);
    bool write(const std::vector<T>& values);
    bool read(T& value);
    bool read(std::vector<T>& values);

    // the methods below are suitable for big data types, where copying data is expensive
    bool writePossible(int n);
    bool readPossible(int n);
    void writeDone(int n);
    void readDone(int n);
    const T* read();
    T* write();

    void setTimeout(int timeout);

    int size();

  private:
    void incrementIndex(int& index);

    int m_size;
    std::vector<T> m_data;
    QSemaphore* m_usedSpace = nullptr;
    QSemaphore* m_freeSpace = nullptr;
    int m_readIndex = 0;
    int m_writeIndex = 0;
    int m_timeout = 100;
};

template<typename T>
T* RingBuffer<T>::write()
{
  T* result = &m_data[m_writeIndex];
  incrementIndex(m_writeIndex);
  return result;
}

template<typename T>
const T* RingBuffer<T>::read()
{
  const T* result = &m_data[m_readIndex];
  incrementIndex(m_readIndex);
  return result;
}

template<typename T>
void RingBuffer<T>::readDone(int n)
{
  m_freeSpace->release(n);
}

template<typename T>
void RingBuffer<T>::writeDone(int n)
{
  m_usedSpace->release(n);
}

template<typename T>
bool RingBuffer<T>::readPossible(int n)
{
  return m_usedSpace->tryAcquire(n, m_timeout);
}

template<typename T>
bool RingBuffer<T>::writePossible(int n)
{
  return m_freeSpace->tryAcquire(n, m_timeout);
}

template<typename T>
void RingBuffer<T>::setTimeout(int timeout)
{
  m_timeout = timeout;
}

template<typename T>
void RingBuffer<T>::incrementIndex(int& index)
{
  index = (index + 1) % m_size;
}

template<typename T>
bool RingBuffer<T>::write(T value)
{
  if (m_freeSpace->tryAcquire(1, m_timeout))
  {
    m_data[m_writeIndex] = value;
    incrementIndex(m_writeIndex);
    m_usedSpace->release(1);
    return true;
  }
  else
  {
    return false;
  }
}

template<typename T>
bool RingBuffer<T>::write(const std::vector<T>& values)
{
  int size = values.size();
  if (m_freeSpace->tryAcquire(size, m_timeout))
  {
    // TODO is there a more performant way with std? Take care of "index-overflow"
    for (int i = 0; i < size; ++i)
    {
      m_data[m_writeIndex] = values[i];
      incrementIndex(m_writeIndex);
    }

    m_usedSpace->release(size);
    return true;
  }
  else
  {
    return false;
  }
}

template<typename T>
bool RingBuffer<T>::read(T& value)
{
  if (m_usedSpace->tryAcquire(1, m_timeout))
  {
    value = m_data[m_readIndex];
    incrementIndex(m_readIndex);
    m_freeSpace->release(1);
    return true;
  }
  else
  {
    return false;
  }
}

template<typename T>
bool RingBuffer<T>::read(std::vector<T>& values)
{
  int size = values.size();
  if (m_usedSpace->tryAcquire(size, m_timeout))
  {
    for (int i = 0; i < size; ++i)
    {
      values[i] = m_data[m_readIndex];
      incrementIndex(m_readIndex);
    }

    m_freeSpace->release(size);
    return true;
  }
  else
  {
    return false;
  }
}

template<typename T>
int RingBuffer<T>::size()
{
  return m_size;
}

template<typename T>
RingBuffer<T>::~RingBuffer()
{
  delete m_usedSpace;
  delete m_freeSpace;
}

template<typename T>
RingBuffer<T>::RingBuffer(int size) :
  m_size(size)
{
  m_data.resize(m_size);
  m_usedSpace = new QSemaphore(0);
  m_freeSpace = new QSemaphore(m_size);
}

#endif