#include <QSettings>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new MainWindowUi)
{
  ui->setupUi(this);
  setWindowTitle("NumberEditTest");

  m_settings = new QSettings("Ulle", "NumberEditTest", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());

  delete ui;
}
