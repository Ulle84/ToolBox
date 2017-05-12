#include "Template.h"
#include "ui_Template.h"

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
