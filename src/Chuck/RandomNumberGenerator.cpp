#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator()
{

}

RandomNumberGenerator::~RandomNumberGenerator()
{

}

void RandomNumberGenerator::run()
{
  m_running = true;

  while (m_running)
  {
    int range = m_maximum - m_minimum + 1;

    int newNumber = rand() % range;
    newNumber += m_minimum;

    newNumberGenerated(newNumber);

    msleep(1000);
  }
}

void RandomNumberGenerator::stop()
{
  m_running = false;


}