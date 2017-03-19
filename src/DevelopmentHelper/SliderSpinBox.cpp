#include <QDebug>

#include "SliderSpinBox.h"
#include "ui_SliderSpinBox.h"

SliderSpinBox::SliderSpinBox(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::SliderSpinBox)
{
  ui->setupUi(this);

  connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
  connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->spinBox, SLOT(setValue(int)));

  connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

SliderSpinBox::~SliderSpinBox()
{
  delete ui;
}

int SliderSpinBox::value()
{
  return ui->spinBox->value();
}

void SliderSpinBox::setValue(int value)
{
  ui->spinBox->setValue(value);
  ui->horizontalSlider->setValue(value);
}

void SliderSpinBox::setMaximum(int maximum)
{
  ui->spinBox->setMaximum(maximum);
  ui->horizontalSlider->setMaximum(maximum);
}

void SliderSpinBox::setMinimum(int minimum)
{
  ui->spinBox->setMinimum(minimum);
  ui->horizontalSlider->setMinimum(minimum);
}

void SliderSpinBox::setText(QString text)
{
  ui->label->setText(text);
}
