#include "QtWidgetsApplication.h"
#include "QtWidgetsApplicationUi.h"

QtWidgetsApplication::QtWidgetsApplication(QWidget* parent) :
  QWidget(parent),
  ui(new QtWidgetsApplicationUi)
{
  ui->setupUi(this);
}

QtWidgetsApplication::~QtWidgetsApplication()
{
  delete ui;
}
