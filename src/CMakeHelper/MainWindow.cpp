#include <QFileDialog>
#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("CMake Helper");

  m_settings = new QSettings("Ulle", "CMakeHelper", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("directories"))
  {
    ui->plainTextEditDirectories->setPlainText(m_settings->value("directories").toString());
  }

  if (m_settings->contains("searchString"))
  {
    ui->lineEdit->setText(m_settings->value("searchString").toString());
  }

  connect(&m_cMakeHelper, &CMakeHelper::notifyProgress, ui->plainTextEditOuput, &QPlainTextEdit::setPlainText);
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("searchString", ui->lineEdit->text());
  m_settings->setValue("directories", ui->plainTextEditDirectories->toPlainText());

  delete ui;
}

void MainWindow::on_pushButtonSearch_clicked()
{
  QString searchString = ui->lineEdit->text();
  QStringList directories = ui->plainTextEditDirectories->toPlainText().split('\n', QString::SkipEmptyParts);

  ui->plainTextEditOuput->setPlainText(tr("searching for files..."));
  QApplication::processEvents();

  QString files = m_cMakeHelper.files(directories, searchString).join('\n');

  if (files.isEmpty())
  {
    ui->plainTextEditOuput->setPlainText(tr("nothing found"));
  }
  else
  {
    ui->plainTextEditOuput->setPlainText(files);
  }
}