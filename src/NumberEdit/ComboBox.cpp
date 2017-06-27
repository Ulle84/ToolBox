// created on 2017-06-26 by Ulrich Belitz

#include "ComboBox.h"

ComboBox::ComboBox(QWidget* parent) :
  QComboBox(parent)
{
}

void ComboBox::setUnit(const QString& unit)
{
  m_unit = unit;
}

void ComboBox::paintEvent(QPaintEvent* event)
{
  if (!m_unit.isEmpty())
  {
    QComboBox::paintEvent(event);
  }
}
