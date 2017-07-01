// created on 2017-01-06 by Ulrich Belitz

#include <QSettings>
#include <QMessageBox>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(const QString& input, QWidget* parent) :
  QMainWindow(parent),
  ui(new MainWindowUi),
  m_input(input)
{
  ui->setupUi(this);
  setWindowTitle("Link Creator");
  setWindowIcon(QIcon(":/images/logo.png"));

  m_settings = new QSettings("Ulle", "LinkCreator", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  ui->lineEditDirectory->setText(m_settings->value("directory").toString());

  ui->lineEditName->setText(input.split('\\', QString::SkipEmptyParts).last());
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("directory", ui->lineEditDirectory->text());

  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  createLink();
}

void MainWindow::on_lineEditName_returnPressed()
{
  createLink();
}

void MainWindow::createLink()
{
  QString linkPath = QString("%1\\%2.lnk").arg(ui->lineEditDirectory->text()).arg(ui->lineEditName->text());

  bool linked = m_input.link(linkPath);

  if (linked)
  {
    QApplication::quit();
  }
  else
  {
    QMessageBox messageBox;
    messageBox.setText(tr("file could not be linked"));
    messageBox.exec();
  }
}
