#include "ListEditTest.h"
#include "ui_ListEditTest.h"

ListEditTest::ListEditTest(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::ListEditTest)
{
  ui->setupUi(this);
}

ListEditTest::~ListEditTest()
{
  delete ui;
}
