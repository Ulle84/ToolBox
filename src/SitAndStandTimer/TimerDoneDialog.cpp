#include <QSettings>

#include "TimerDoneDialog.h"
#include "ui_TimerDoneDialog.h"

TimerDoneDialog::TimerDoneDialog(QWidget* parent) :
  QDialog(parent),
  ui(new Ui::TimerDoneDialog),
  m_nextPosition(Undefined)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "SitAndStandTimer");

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

TimerDoneDialog::NextPosition TimerDoneDialog::nextPosition()
{
  return m_nextPosition;
}

void TimerDoneDialog::on_pushButtonStartSitting_clicked()
{
  m_nextPosition = Sitting;
  accept();
}

void TimerDoneDialog::on_pushButtonStartStanding_clicked()
{
  m_nextPosition = Standing;
  accept();
}

void TimerDoneDialog::on_pushButtonClose_clicked()
{
  m_nextPosition = Undefined;
  accept();
}
