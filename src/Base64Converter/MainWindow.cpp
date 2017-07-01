#include <QSettings>
#include <QString>
#include <QByteArray>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new MainWindowUi)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "Base64Converter", this);

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

void MainWindow::on_plainTextEditBase64_textChanged()
{
  QByteArray ba;
  ba.append(ui->plainTextEditBase64->toPlainText());

  ui->plainTextEditPlain->blockSignals(true);
  ui->plainTextEditPlain->setPlainText(QByteArray::fromBase64(ba).data());
  ui->plainTextEditPlain->blockSignals(false);

}

void MainWindow::on_plainTextEditPlain_textChanged()
{
  QByteArray ba;
  ba.append(ui->plainTextEditPlain->toPlainText());

  ui->plainTextEditBase64->blockSignals(true);
  ui->plainTextEditBase64->setPlainText(ba.toBase64().data());
  ui->plainTextEditBase64->blockSignals(false);
}
