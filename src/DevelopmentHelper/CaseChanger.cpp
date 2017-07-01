// created on 2017-02-23 by Ulrich Belitz

#include <QClipboard>

#include "CaseChanger.h"
#include "CaseChangerUi.h"

CaseChanger::CaseChanger(QWidget* parent) :
  QWidget(parent),
  ui(new CaseChangerUi)
{
  ui->setupUi(this);
}

CaseChanger::~CaseChanger()
{
  delete ui;
}

void CaseChanger::on_pushButtonUppercase_clicked()
{
  QApplication::clipboard()->setText(ui->lineEdit->text().toUpper());
}

void CaseChanger::on_pushButtonLowercase_clicked()
{
  QApplication::clipboard()->setText(ui->lineEdit->text().toLower());
}
