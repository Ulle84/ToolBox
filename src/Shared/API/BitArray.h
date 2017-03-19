// created on 2016-12-08

#ifndef BITARRAY_H
#define BITARRAY_H

#include <iostream>
#include <string>

#include "CustomTypes.h"

// Note: curently the indexes have 8 bit
//       if you have systems with more than 256 bit, all occurences with uint8 have to be replaced by uint16!

template<typename T>
class BitArray
{
  public:
    BitArray(uint8 nUsedBits = 0);

    void useAllBits();
    void setUsedBits(uint8 nUsedBits);

    void setBit(uint8 index);
    void clearBit(uint8 index);
    bool isBitSet(uint8 index);
    void toggleBit(uint8 index);
    bool allBitsSet();

    void setAllBits();
    void clearAllBits();

    void printAllBits();
    std::string information();

    uint8 availableBits();

  private:
    T m_bitArray = 0;
    uint8 m_nUsedBits;
};

template<typename T>
std::string BitArray<T>::information()
{
  std::string bits;
  for (uint8 i = m_nUsedBits - 1;; --i)
  {
    if (isBitSet(i))
    {
      bits.push_back('X');
    }
    else
    {
      bits.push_back('.');
    }

    if (i == 0)
    {
      break;
    }

    if (i % 8 == 0)
    {
      bits.push_back(' ');
    }
  }

  return bits;
}

template<typename T>
uint8 BitArray<T>::availableBits()
{
  return m_nUsedBits;
}

template<typename T>
BitArray<T>::BitArray(uint8 nUsedBits)
{
  setUsedBits(nUsedBits);
}

template<typename T>
void BitArray<T>::setUsedBits(uint8 nUsedBits)
{
  uint8 maxAvailableBits = sizeof(T) * 8;

  if (nUsedBits == 0 || nUsedBits > maxAvailableBits)
  {
    nUsedBits = maxAvailableBits;
  }

  m_nUsedBits = nUsedBits;
}

template<typename T>
void BitArray<T>::useAllBits()
{
  setUsedBits(0);
}

template<typename T>
void BitArray<T>::setBit(uint8 index)
{
  if (index > m_nUsedBits)
  {
    return;
  }

  m_bitArray |= (T)1 << index;
}

template<typename T>
bool BitArray<T>::isBitSet(uint8 index)
{
  if (index > m_nUsedBits)
  {
    return false;
  }

  return (m_bitArray >> index) & 1;
}

template<typename T>
void BitArray<T>::toggleBit(uint8 index)
{
  m_bitArray ^= (T)1 << index;
}

template<typename T>
void BitArray<T>::clearBit(uint8 index)
{
  if (index > m_nUsedBits)
  {
    return;
  }

  m_bitArray &= ~((T)1 << index);
}

template<typename T>
void BitArray<T>::setAllBits()
{
  if (m_nUsedBits == sizeof(T) * 8)
  {
    m_bitArray = (T) - 1;
  }
  else
  {
    for (uint8 i = 0; i < m_nUsedBits; ++i)
    {
      setBit(i);
    }
  }
}

template<typename T>
bool BitArray<T>::allBitsSet()
{
  if (m_nUsedBits == sizeof(T) * 8)
  {
    return (m_bitArray == (T) - 1);
  }
  else
  {
    // TODO do more performant with bitshift-created bitmask
    bool allBitsSet = true;
    for (uint8 i = 0; i < m_nUsedBits; ++i)
    {
      allBitsSet &= isBitSet(i);
    }
    return allBitsSet;
  }
}

template<typename T>
void BitArray<T>::clearAllBits()
{
  m_bitArray = 0;
}

template<typename T>
void BitArray<T>::printAllBits()
{
  std::cout << information() << std::endl;
}

#endif