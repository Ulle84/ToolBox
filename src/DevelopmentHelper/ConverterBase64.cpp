#include <QString>
#include <QByteArray>

#include "ConverterBase64.h"
#include "ConverterBase64Ui.h"

ConverterBase64::ConverterBase64(QWidget* parent) :
  QWidget(parent),
  ui(new ConverterBase64Ui)
{
  ui->setupUi(this);
}

ConverterBase64::~ConverterBase64()
{
  delete ui;
}

void ConverterBase64::on_lineEditPlainText_editingFinished()
{
  QByteArray ba;
  ba.append(ui->lineEditPlainText->text());
  ui->lineEditBase64EncodedText->setText(ba.toBase64().data());
}

void ConverterBase64::on_lineEditBase64EncodedText_editingFinished()
{
  QByteArray ba;
  ba.append(ui->lineEditBase64EncodedText->text());
  ui->lineEditPlainText->setText(QByteArray::fromBase64(ba).data());
}
