#include "QtWidgetDll.h"
#include "QtWidgetDllUi.h"

QtWidgetDll::QtWidgetDll(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::QtWidgetDll)
{
  ui->setupUi(this);
}

QtWidgetDll::~QtWidgetDll()
{
  delete ui;
}
