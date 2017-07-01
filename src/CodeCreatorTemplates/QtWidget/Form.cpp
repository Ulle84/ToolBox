#include "Form.h"
#include "FormUi.h"

Form::Form(QWidget* parent) :
  QWidget(parent),
  ui(new FormUi)
{
  ui->setupUi(this);
}

Form::~Form()
{
  delete ui;
}
