#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QIcon>
#include <QMenu>

#include "TimerDoneDialog.h"
#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new MainWindowUi)
{
  ui->setupUi(this);

  m_icon = QIcon(":/images/logo.ico");
  setWindowIcon(m_icon);
  setWindowTitle("Timer");

  m_settings = new QSettings("Ulle", "Timer");

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  m_timer = new QTimer(this);
  m_timer->start(1000);
  connect(m_timer, &QTimer::timeout, this, &MainWindow::update);
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());

  delete ui;
}

void MainWindow::update()
{
  if (m_state == Stopped)
  {
    ui->statusBar->clearMessage();
  }
  else
  {
    quint64 secondsDiff = QDateTime::currentDateTime().secsTo(m_dateTimeEnd);

    if (secondsDiff > 0)
    {
      QString message = tr("Remaining time: ");
      message.append(timeToString(secondsDiff / 60, secondsDiff % 60));

      ui->statusBar->showMessage(message);
    }
    else
    {
      // timer done
      ui->statusBar->clearMessage();

      QString message = tr("time is over");

      m_state = Stopped;

      TimerDoneDialog timerDoneDialog;
      timerDoneDialog.setWindowTitle(message);
      timerDoneDialog.setWindowFlags(Qt::WindowStaysOnTopHint);
      timerDoneDialog.exec();
    }
  }
}

void MainWindow::on_pushButton1_clicked()
{
  startTimer(1 * 60);
}

void MainWindow::on_pushButton2_clicked()
{
  startTimer(2 * 60);
}

void MainWindow::on_pushButton3_clicked()
{
  startTimer(3 * 60);
}

void MainWindow::on_pushButton4_clicked()
{
  startTimer(4 * 60);
}

void MainWindow::on_pushButton5_clicked()
{
  startTimer(5 * 60);
}

void MainWindow::on_pushButton6_clicked()
{
  startTimer(6 * 60);
}

void MainWindow::on_pushButton7_clicked()
{
  startTimer(7 * 60);
}

void MainWindow::on_pushButton8_clicked()
{
  startTimer(8 * 60);
}

void MainWindow::on_pushButton9_clicked()
{
  startTimer(9 * 60);
}

void MainWindow::on_pushButton10_clicked()
{
  startTimer(10 * 60);
}

void MainWindow::on_pushButton30_clicked()
{
  startTimer(30 * 60);
}

void MainWindow::startTimer(uint64 seconds)
{
  m_dateTimeEnd = QDateTime::currentDateTime().addSecs(seconds);
  m_state = Running;
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