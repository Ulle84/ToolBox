// created on 2017-01-25 by Ulrich Belitz

#include <QSettings>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new MainWindowUi)
{
  ui->setupUi(this);
  setWindowTitle("ExperimentEditor");
  setWindowIcon(QIcon(":/images/logo.png"));

  m_settings = new QSettings("Ulle", "ExperimentEditor", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("splitter"))
  {
    ui->splitter->restoreState(m_settings->value("splitter").toByteArray());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("splitter", ui->splitter->saveState());

  delete ui;
}
