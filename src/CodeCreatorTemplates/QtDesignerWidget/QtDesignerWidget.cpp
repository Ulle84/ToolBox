#include "QtDesignerWidget.h"
#include "QtDesignerWidgetUi.h"

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
