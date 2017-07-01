#include <QSettings>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  setWindowTitle("AutoHotKey Helper");

  m_settings = new QSettings("Ulle", "AutoHotKeyHelper", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("file"))
  {
    ui->lineEditFile->setText(m_settings->value("file").toString());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("file", ui->lineEditFile->text());

  delete ui;
}

void MainWindow::on_pushButtonSelectFile_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("select folder"), ui->lineEditFile->text());

  if (!fileName.isEmpty())
  {
    ui->lineEditFile->setText(fileName);
  }
}

void MainWindow::on_pushButtonAppendToFile_clicked()
{
  m_autoHotKeyHelper.appendToFile(ui->lineEditFile->text(), ui->lineEditKey->text(), ui->lineEditContent->text());
}

void MainWindow::on_lineEditFile_textChanged(const QString& text)
{
  m_autoHotKeyHelper.parseKeys(text);
}

void MainWindow::on_lineEditKey_textChanged(const QString& text)
{
  ui->lineEditKey->setStyleSheet(QString("background-color: rgb(255, %1, %1)").arg(m_autoHotKeyHelper.isKeyContained(text) ? "200" : "255"));
}
