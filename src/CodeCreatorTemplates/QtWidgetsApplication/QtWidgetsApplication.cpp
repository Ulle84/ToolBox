#include "QtWidgetsApplication.h"
#include "ui_QtWidgetsApplication.h"

QtWidgetsApplication::QtWidgetsApplication(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::QtWidgetsApplication)
{
  ui->setupUi(this);
}

QtWidgetsApplication::~QtWidgetsApplication()
{
  delete ui;
}
