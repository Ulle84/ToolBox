#include "Template.h"
#include "TemplateUi.h"

Template::Template(QWidget* parent) :
  QDialog(parent),
  ui(new TemplateUi)
{
  ui->setupUi(this);
}

Template::~Template()
{
  delete ui;
}
