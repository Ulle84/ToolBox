// created on 2017-06-20 by Ulrich Belitz

#include <cmath>

#include <QDebug>

#include "NumberEdit.h"
#include "NumberEditUi.h"

NumberEdit::NumberEdit(QWidget* parent) :
  GridLayoutable(parent),
  ui(new NumberEditUi)
{
  m_supportedMin = -std::numeric_limits<double>::max() / std::pow(10, m_maxExponent);
  m_supportedMax = std::numeric_limits<double>::max() / std::pow(10, m_maxExponent);

  m_minimum = m_supportedMin;
  m_maximum = m_supportedMax;

  m_lowerLimit = m_supportedMin;
  m_upperLimit = m_supportedMax;

  ui->setupUi(this);

  ui->label->setVisible(false);
  ui->comboBox->setVisible(false);
}

NumberEdit::~NumberEdit()
{
  delete ui;
}

void NumberEdit::setLabel(const QString& label)
{
  ui->label->setMinimumWidth(0);
  ui->label->setText(label);
  m_labelWidth = label.isEmpty() ? 0 : ui->label->minimumSizeHint().width();

  if (isGridLayouted())
  {
    updateWidths();
  }
  else
  {
    updateLabelDisplay(m_labelWidth);
  }
}

QString NumberEdit::label()
{
  return ui->label->text();
}

void NumberEdit::setUnit(const QString& unit)
{
  m_unit = unit;
  setupUnitSelector();
  updateControl();

  if(isGridLayouted())
  {
    updateWidths();
  }
  else
  {
    updateUnitDisplay(m_unitWidth);
  }
}

QString NumberEdit::unit()
{
  return m_unit;
}

void NumberEdit::setValue(double value)
{
  m_value = value;
  updateControl();
}

double NumberEdit::value()
{
  return m_value;
}

int NumberEdit::toInt()
{
  return m_value > 0 ? m_value + 0.5 : m_value - 0.5;
}

double NumberEdit::toDouble()
{
  return m_value;
}

void NumberEdit::setMinimum(double minimum)
{
  if (minimum < m_supportedMin)
  {
    m_minimum = m_supportedMin;
  }
  else
  {
    m_minimum = minimum;
  }

  updateControl();
}

double NumberEdit::minimum()
{
  return m_minimum;
}

void NumberEdit::setMaximum(double maximum)
{
  if (maximum > m_supportedMax)
  {
    m_maximum = m_supportedMax;
  }
  else
  {
    m_maximum = maximum;
  }

  updateControl();
}

double NumberEdit::maximum()
{
  return m_maximum;
}

void NumberEdit::setDecimals(int decimals)
{
  ui->doubleSpinBox->setDecimals(decimals);
}

int NumberEdit::decimals()
{
  return ui->doubleSpinBox->decimals();
}

void NumberEdit::setLowerLimit(double lowerLimit)
{
  m_lowerLimit = lowerLimit;
  updateControl();
}

double NumberEdit::lowerLimit()
{
  return m_lowerLimit;
}

void NumberEdit::setUpperLimit(double upperLimit)
{
  m_upperLimit = upperLimit;
  updateControl();
}

double NumberEdit::upperLimit()
{
  return m_upperLimit;
}

//void NumberEdit::setWarningFactor(double warningFactor)
//{
//  m_warningFactor = warningFactor;
//  updateControl();
//}
//
//double NumberEdit::warningFactor()
//{
//  return m_warningFactor;
//}

void NumberEdit::setUnitWidth(int unitWidth)
{
  m_unitWidth = unitWidth;

  if (isGridLayouted())
  {
    updateWidths();
  }
  else
  {
    updateUnitDisplay(m_unitWidth);
  }  
}

int NumberEdit::unitWidth()
{
  return m_unitWidth;
}

QVector<int> NumberEdit::minimumWidths()
{
  QVector<int> list;

  list.append(m_labelWidth);
  list.append(0);
  list.append(m_unit.isEmpty() ? 0 : m_unitWidth);

  return list;
}

void NumberEdit::setMinimumWidths(const QVector<int>& widths)
{
  if (widths.length() < 3)
  {
    return;
  }

  updateLabelDisplay(widths[0]);
  updateUnitDisplay(widths[2]);
}

void NumberEdit::resetMinumumWidths()
{
  ui->label->setMinimumWidth(0);
  ui->comboBox->setMinimumWidth(m_unitWidth);
}

void NumberEdit::on_doubleSpinBox_valueChanged(double value)
{
  int exponent = ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();
  m_value = value * std::pow(10, exponent);
  applyLimits();
}

void NumberEdit::on_comboBox_currentIndexChanged(int index)
{
  updateControl();
}

void NumberEdit::setupUnitSelector()
{
  disconnect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_currentIndexChanged(int)));

  ui->comboBox->setUnit(m_unit);

  ui->comboBox->clear();

  if (!m_unit.isEmpty())
  {
    // Attention: m_maxExponent needs to be updated if range is expanded!

    ui->comboBox->addItem("p" + m_unit, -12);
    ui->comboBox->addItem("n" + m_unit, -9);
    ui->comboBox->addItem(QChar(0x03BC) + m_unit, -6);
    ui->comboBox->addItem("m" + m_unit, -3);
    ui->comboBox->addItem(m_unit, 0);
    ui->comboBox->addItem("k" + m_unit, 3);
    ui->comboBox->addItem("M" + m_unit, 6);
    ui->comboBox->addItem("G" + m_unit, 9);

    ui->comboBox->setCurrentIndex(4); // select base unit with potency 0
  }

  connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_currentIndexChanged(int)));
}

void NumberEdit::updateControl()
{
  int exponent = m_unit.isEmpty() ? 0 : ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();

  disconnect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(on_doubleSpinBox_valueChanged(double)));
  ui->doubleSpinBox->setRange(m_minimum / std::pow(10, exponent), m_maximum / std::pow(10, exponent));
  ui->doubleSpinBox->setValue(m_value / std::pow(10, exponent));
  connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(on_doubleSpinBox_valueChanged(double)));

  applyLimits();
}

void NumberEdit::setRange(double minimum, double maximum)
{
  setMinimum(minimum);
  setMaximum(maximum);
}

void NumberEdit::applyLimits()
{
  bool showWarning = false;

  if (m_value < m_lowerLimit)
  {
    showWarning = true;
  }
  else if (m_value > m_upperLimit)
  {
    showWarning = true;
  }

  //if (m_warningFactor != 0.0)
  //{
  //  double range = m_maximum - m_minimum;
  //  double offset = range * (1.0 - m_warningFactor) / 2;
  //  double warnLower = m_minimum + offset;
  //  double warnUpper = m_maximum - offset;
  //
  //  if (m_value < warnLower)
  //  {
  //    showWarning = true;
  //  }
  //  else if (m_value > warnUpper)
  //  {
  //    showWarning = true;
  //  }
  //}

  ui->doubleSpinBox->setStyleSheet(QString("background-color: %1").arg(showWarning ? "rgba(255, 255, 0, 0.4)" : "rgba(255, 255, 255, 1.0)"));
}

void NumberEdit::updateLabelDisplay(int width)
{
  bool visible = true;

  if (ui->label->text().isEmpty())
  {
    if (!isGridLayouted())
    {
      visible = false;
    }
    else
    {
      if (width == 0)
      {
        visible = false;
      }
    }
  }

  ui->label->setMinimumWidth(width);
  ui->label->setVisible(visible);
}

void NumberEdit::updateUnitDisplay(int width)
{
  bool visible = true;

  if (m_unit.isEmpty())
  {
    if (!isGridLayouted())
    {
      visible = false;
    }
    else
    {
      if (width == 0)
      {
        visible = false;
      }
    }
  }

  //if (m_unit.isEmpty() && width != 0)
  //{
  //  int test = rand();
  //}

  ui->comboBox->setMinimumWidth(visible ? width : 0);
  ui->comboBox->setMaximumWidth(visible ? width : 0);
  ui->comboBox->setVisible(visible);
}
