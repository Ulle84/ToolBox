#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QIcon>
#include <QMenu>

#include "TimerDoneDialog.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_icon = QIcon(":/images/logo.png");
  setWindowIcon(m_icon);

  m_settings = new QSettings("Ulle", "SitAndStandTimer");

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("standTime"))
  {
    ui->spinBoxStandTime->setValue(m_settings->value("standTime").toInt());
  }

  if (m_settings->contains("sitTime"))
  {
    ui->spinBoxSitTime->setValue(m_settings->value("sitTime").toInt());
  }

  m_state = Undefined;

  m_timer = new QTimer(this);
  m_timer->start(1000);
  connect(m_timer, &QTimer::timeout, this, &MainWindow::update);
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("standTime", ui->spinBoxStandTime->value());
  m_settings->setValue("sitTime", ui->spinBoxSitTime->value());

  delete ui;
}

void MainWindow::update()
{
  if (m_state == Undefined)
  {
    ui->statusBar->clearMessage();
  }
  else
  {
    quint64 secondsDiff = QDateTime::currentDateTime().secsTo(m_dateTimeEnd);

    if (secondsDiff > 0)
    {
      QString message = tr("Remaining ");

      if (m_state == Sitting)
      {
        message.append(tr("sitting"));
      }
      else if (m_state == Standing)
      {
        message.append(tr("standing"));
      }

      message.append(tr(" time: "));
      message.append(timeToString(secondsDiff / 60, secondsDiff % 60));

      ui->statusBar->showMessage(message);
    }
    else
    {
      // timer done
      ui->statusBar->clearMessage();

      QString message;

      if (m_state == Sitting)
      {
        message.append(tr("sitting"));
      }
      else if (m_state == Standing)
      {
        message.append(tr("standing"));
      }

      message.append(tr(" time is over!"));

      m_state = Undefined;

      TimerDoneDialog timerDoneDialog;
      timerDoneDialog.setWindowTitle(message);
      timerDoneDialog.setWindowFlags(Qt::WindowStaysOnTopHint);
      timerDoneDialog.exec();

      TimerDoneDialog::NextPosition nextPosition = timerDoneDialog.nextPosition();

      if (nextPosition == Sitting)
      {
        startSitting();
      }
      else if (nextPosition == Standing)
      {
        startStanding();
      }
    }
  }
}

void MainWindow::on_pushButtonStartSitting_clicked()
{
  startSitting();
}

void MainWindow::on_pushButtonStartStanding_clicked()
{
  startStanding();
}

void MainWindow::startSitting()
{
  m_state = Sitting;
  m_dateTimeEnd = QDateTime::currentDateTime().addSecs(ui->spinBoxSitTime->value() * 60);
  update();
}

void MainWindow::startStanding()
{
  m_state = Standing;
  m_dateTimeEnd = QDateTime::currentDateTime().addSecs(ui->spinBoxStandTime->value() * 60);
  update();
}

QString MainWindow::timeToString(int minutes, int seconds)
{
  QString time;

  if (minutes < 10)
  {
    time.append("0");
  }

  time.append(QString("%1:").arg(minutes));

  if (seconds < 10)
  {
    time.append("0");
  }

  time.append(QString("%1").arg(seconds));

  return time;
}