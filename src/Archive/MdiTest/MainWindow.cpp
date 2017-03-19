// created on 2017-02-15 by Ulrich Belitz

#include <QSettings>
#include <QMdiSubWindow>
#include <QPushButton>
#include <QTextEdit>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("MdiTest");
  setWindowIcon(QIcon(":/images/logo.png"));

  m_settings = new QSettings("Ulle", "MdiTest", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  for (int i = 0; i < 8; ++i)
  {
    QString id = QString("window %1").arg(i);
    QMdiSubWindow* subWindow = ui->mdiArea->addSubWindow(new QTextEdit(id));
    subWindow->setWindowTitle(id);
  }
    
  QList<QMdiSubWindow*> subWindows = ui->mdiArea->subWindowList();
  for (auto& it : subWindows)
  {
    it->resize(400, 400);
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());

  delete ui;
}
