#include "SlashConverter.h"

#include "TextConverter.h"
#include "TextConverterUi.h"

TextConverter::TextConverter(QWidget* parent) :
  QWidget(parent),
  ui(new TextConverterUi)
{
  ui->setupUi(this);

  SlashConverter* slashConverter = new SlashConverter(this);
  ui->groupBoxSlashConverter->layout()->addWidget(slashConverter);
}

TextConverter::~TextConverter()
{
  delete ui;
}
