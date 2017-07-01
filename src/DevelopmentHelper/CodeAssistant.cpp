#include <QClipboard>

#include "EnumHelper.h"

#include "CodeAssistant.h"
#include "CodeAssistantUi.h"

CodeAssistant::CodeAssistant(QWidget* parent) :
  QWidget(parent),
  ui(new CodeAssistantUi)
{
  ui->setupUi(this);

  EnumHelper* enumHelper = new EnumHelper(this);

  ui->container->layout()->addWidget(enumHelper);
}

CodeAssistant::~CodeAssistant()
{
  delete ui;
}
