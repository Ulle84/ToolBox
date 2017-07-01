#include "Template.h"
#include "TemplateUi.h"

Template::Template(QWidget* parent) :
  QDialog(parent),
  ui(new Ui::Template)
{
  ui->setupUi(this);
}

Template::~Template()
{
  delete ui;
}
