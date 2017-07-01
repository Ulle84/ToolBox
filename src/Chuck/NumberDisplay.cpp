#include <QTimer>

#include "NumberDisplay.h"
#include "NumberDisplayUi.h"

NumberDisplay::NumberDisplay(QWidget* parent) :
  QWidget(parent),
  ui(new NumberDisplayUi)
{
  m_timer = new QTimer(this);
  bool success = connect(m_timer, &QTimer::timeout, this, &NumberDisplay::update);
  m_timer->start(100);

  ui->setupUi(this);
}

NumberDisplay::~NumberDisplay()
{
  delete ui;
}

void NumberDisplay::setNewGeneratedNumber(int newNumber)
{
  m_currentNumber = newNumber;
}

void NumberDisplay::update()
{
  ui->label->setText(QString::number(m_currentNumber));
}
