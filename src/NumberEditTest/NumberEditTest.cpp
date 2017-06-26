#include "NumberEditTest.h"
#include "ui_NumberEditTest.h"

NumberEditTest::NumberEditTest(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::NumberEditTest)
{
  ui->setupUi(this);
}

NumberEditTest::~NumberEditTest()
{
  delete ui;
}
