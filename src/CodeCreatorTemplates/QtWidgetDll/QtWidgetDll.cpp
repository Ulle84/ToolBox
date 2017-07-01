#include "QtWidgetDll.h"
#include "QtWidgetDllUi.h"

QtWidgetDll::QtWidgetDll(QWidget* parent) :
  QWidget(parent),
  ui(new QtWidgetDllUi)
{
  ui->setupUi(this);
}

QtWidgetDll::~QtWidgetDll()
{
  delete ui;
}
