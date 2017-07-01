#include "ListEditTest.h"
#include "ListEditTestUi.h"

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
