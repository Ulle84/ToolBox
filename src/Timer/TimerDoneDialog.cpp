#include <QSettings>

#include "TimerDoneDialog.h"
#include "TimerDoneDialogUi.h"

TimerDoneDialog::TimerDoneDialog(QWidget* parent) :
  QDialog(parent),
  ui(new Ui::TimerDoneDialog)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "Timer");

  if (m_settings->contains("dialogGeometry"))
  {
    setGeometry(m_settings->value("dialogGeometry").toRect());
  }
}

TimerDoneDialog::~TimerDoneDialog()
{
  m_settings->setValue("dialogGeometry", geometry());

  delete ui;
}

void TimerDoneDialog::on_pushButtonClose_clicked()
{
  accept();
}
