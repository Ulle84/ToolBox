// created on 2017-03-15 by Ulrich Belitz

#include "SimpleHtmlEdit.h"
#include "ui_SimpleHtmlEdit.h"

#include "SimpleHtmlConverter.h"

SimpleHtmlEdit::SimpleHtmlEdit(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::SimpleHtmlEdit)
{
  ui->setupUi(this);
  ui->tabWidget->setTabText(0, tr("HTML code"));
  ui->tabWidget->setTabText(1, tr("HTML preview"));
  ui->codeEditSimpleHtml->setCodeHighlightingType(CodeEdit::CodeHighlightingType::SimpleHtml);
  ui->codeEditHtml->setCodeHighlightingType(CodeEdit::CodeHighlightingType::Xml);
}

SimpleHtmlEdit::~SimpleHtmlEdit()
{
  delete ui;
}

void SimpleHtmlEdit::setText(const QString& text)
{
  ui->codeEditSimpleHtml->setPlainText(text);
}

QString SimpleHtmlEdit::text()
{
  return ui->codeEditSimpleHtml->toPlainText();
}

void SimpleHtmlEdit::setSplitterState(const QByteArray& state)
{
  ui->splitter->restoreState(state);
}

QByteArray SimpleHtmlEdit::splitterState()
{
  return ui->splitter->saveState();
}

void SimpleHtmlEdit::on_codeEditSimpleHtml_textChanged()
{
  SimpleHtmlConverter converter;

  QString html = converter.toHtml(ui->codeEditSimpleHtml->toPlainText());

  ui->codeEditHtml->setPlainText(html);
  ui->textBrowser->setText(html);
}
