#include "Converter.h"
#include "ConverterUi.h"

Converter::Converter(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::Converter)
{
  ui->setupUi(this);
}

Converter::~Converter()
{
  delete ui;
}
