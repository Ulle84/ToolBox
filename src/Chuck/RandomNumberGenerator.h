#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <QThread>

class RandomNumberGenerator : public QThread
{
  Q_OBJECT

public:
  RandomNumberGenerator();
  ~RandomNumberGenerator();

  void run();
  void stop();

signals:
  void newNumberGenerated(int newNumber);

private:
  volatile bool m_running = false;

  int m_minimum = 0;
  int m_maximum = 9;
};

#endif