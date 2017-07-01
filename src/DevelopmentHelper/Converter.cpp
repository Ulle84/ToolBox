#include "Converter.h"
#include "ConverterUi.h"

Converter::Converter(QWidget* parent) :
  QWidget(parent),
  ui(new ConverterUi)
{
  ui->setupUi(this);
}

Converter::~Converter()
{
  delete ui;
}
