#include <QSettings>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("ListEditTest");

  m_settings = new QSettings("Ulle", "ListEditTest", this);

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
