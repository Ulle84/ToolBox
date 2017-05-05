#include "DailyNotes.h"
#include "ui_DailyNotes.h"

#include "SimpleHtmlConverter.h"

DailyNotes::DailyNotes(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::DailyNotes)
{
  ui->setupUi(this);
  ui->codeEdit->setCodeHighlightingType(CodeEdit::CodeHighlightingType::SimpleHtml);
}

DailyNotes::~DailyNotes()
{
  delete ui;
}

void DailyNotes::on_codeEdit_textChanged()
{
  SimpleHtmlConverter simpleHtmlConverter;
  ui->webView->setHtml(simpleHtmlConverter.toHtml(ui->codeEdit->toPlainText()));
}
