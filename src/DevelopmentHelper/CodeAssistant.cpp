#include <QClipboard>

#include "EnumHelper.h"

#include "CodeAssistant.h"
#include "ui_CodeAssistant.h"

CodeAssistant::CodeAssistant(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::CodeAssistant)
{
  ui->setupUi(this);

  EnumHelper* enumHelper = new EnumHelper(this);

  ui->container->layout()->addWidget(enumHelper);
}

CodeAssistant::~CodeAssistant()
{
  delete ui;
}
