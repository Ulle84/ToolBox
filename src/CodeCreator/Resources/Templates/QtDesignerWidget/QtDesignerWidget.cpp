#include "QtDesignerWidget.h"
#include "ui_QtDesignerWidget.h"

QtDesignerWidget::QtDesignerWidget(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::QtDesignerWidget)
{
  ui->setupUi(this);
}

QtDesignerWidget::~QtDesignerWidget()
{
  delete ui;
}
