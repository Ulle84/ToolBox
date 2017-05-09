// created on 2017-03-15 by Ulrich Belitz

#include "SmlEdit.h"
#include "ui_SmlEdit.h"

#include "Converter.h"

SmlEdit::SmlEdit(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::SmlEdit)
{
  ui->setupUi(this);
  ui->tabWidget->setTabText(0, tr("HTML code"));
  ui->tabWidget->setTabText(1, tr("HTML preview"));
  ui->codeEditSimpleHtml->setCodeHighlightingType(CodeEdit::CodeHighlightingType::Sml);
  ui->codeEditHtml->setCodeHighlightingType(CodeEdit::CodeHighlightingType::Xml);
}

SmlEdit::~SmlEdit()
{
  delete ui;
}

void SmlEdit::setText(const QString& text)
{
  ui->codeEditSimpleHtml->setPlainText(text);
}

QString SmlEdit::text()
{
  return ui->codeEditSimpleHtml->toPlainText();
}

void SmlEdit::setSplitterState(const QByteArray& state)
{
  ui->splitter->restoreState(state);
}

QByteArray SmlEdit::splitterState()
{
  return ui->splitter->saveState();
}

void SmlEdit::on_codeEditSimpleHtml_textChanged()
{
  QString html = Converter::toHtml(ui->codeEditSimpleHtml->toPlainText());

  ui->codeEditHtml->setPlainText(html);
  ui->webView->setHtml(html);
}
