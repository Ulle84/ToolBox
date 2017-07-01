#include "QtDesignerWidget.h"
#include "QtDesignerWidgetUi.h"

QtDesignerWidget::QtDesignerWidget(QWidget* parent) :
  QWidget(parent),
  ui(new QtDesignerWidgetUi)
{
  ui->setupUi(this);
}

QtDesignerWidget::~QtDesignerWidget()
{
  delete ui;
}
