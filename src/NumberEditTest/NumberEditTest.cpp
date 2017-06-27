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

void NumberEditTest::on_pushButton_clicked()
{
  //ui->numberEdit->setLabel("loooooooooooooooooooooooooooooooooooooooong");
  //return;
  
  QLayoutItem* item = ui->verticalLayout->takeAt(0);

  if (item->widget())
  {
    delete item->widget();
  }

  delete item;

}
