#include <QFileDialog>
#include <QSettings>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "IncludeFinder", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("directories"))
  {
    ui->plainTextEditDirectories->setPlainText(m_settings->value("directories").toString());
  }

  if (m_settings->contains("includes"))
  {
    ui->plainTextEditIncludes->setPlainText(m_settings->value("includes").toString());
  }

  connect(&m_includeFinder, &IncludeFinder::notifyProgress, ui->plainTextEditOuput, &QPlainTextEdit::setPlainText);
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("includes", ui->plainTextEditIncludes->toPlainText());
  m_settings->setValue("directories", ui->plainTextEditDirectories->toPlainText());

  delete ui;
}

void MainWindow::on_pushButtonSearch_clicked()
{
  QStringList includes = ui->plainTextEditIncludes->toPlainText().split('\n', QString::SkipEmptyParts);
  QStringList directories = ui->plainTextEditDirectories->toPlainText().split('\n', QString::SkipEmptyParts);

  ui->plainTextEditOuput->setPlainText(tr("searching for files..."));
  QApplication::processEvents();

  QString files = m_includeFinder.files(directories, includes).join('\n');

  if (files.isEmpty())
  {
    ui->plainTextEditOuput->setPlainText(tr("nothing found"));
  }
  else
  {
    ui->plainTextEditOuput->setPlainText(files);
  }
}