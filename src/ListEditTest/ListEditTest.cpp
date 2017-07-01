#include "ListEditTest.h"
#include "ListEditTestUi.h"

ListEditTest::ListEditTest(QWidget* parent) :
  QWidget(parent),
  ui(new ListEditTestUi)
{
  ui->setupUi(this);
}

ListEditTest::~ListEditTest()
{
  delete ui;
}
