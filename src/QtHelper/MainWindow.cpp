#include <QSettings>
#include <QFileDialog>
#include <QProcess>
#include <QDirIterator>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("Qt Helper");

  m_settings = new QSettings("Ulle", "QtHelper", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("lineEditUIC"))
  {
    ui->lineEditUIC->setText(m_settings->value("lineEditUIC").toString());
  }

  if (m_settings->contains("lineEditInputDirectory"))
  {
    ui->lineEditInputDirectory->setText(m_settings->value("lineEditInputDirectory").toString());
  }

  if (m_settings->contains("lineEditOutputDirectory"))
  {
    ui->lineEditOutputDirectory->setText(m_settings->value("lineEditOutputDirectory").toString());
  }

  if (m_settings->contains("lineEditResourceCompiler"))
  {
    ui->lineEditResourceCompiler->setText(m_settings->value("lineEditResourceCompiler").toString());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("lineEditUIC", ui->lineEditUIC->text());
  m_settings->setValue("lineEditInputDirectory", ui->lineEditInputDirectory->text());
  m_settings->setValue("lineEditOutputDirectory", ui->lineEditOutputDirectory->text());
  m_settings->setValue("lineEditResourceCompiler", ui->lineEditResourceCompiler->text());

  delete ui;
}

void MainWindow::on_pushButtonUIC_clicked()
{
  QString uic = QFileDialog::getOpenFileName(this, tr("select UIC.exe"), ui->lineEditUIC->text(), "*.exe");

  if (!uic.isEmpty())
  {
    ui->lineEditUIC->setText(uic);
  }
}

void MainWindow::on_pushButtonInputDirectory_clicked()
{
  QString inputDirectory = QFileDialog::getExistingDirectory(this, tr("select input directory"), ui->lineEditInputDirectory->text());

  if (!inputDirectory.isEmpty())
  {
    ui->lineEditInputDirectory->setText(inputDirectory);
  }
}

void MainWindow::on_pushButtonOutputDirectory_clicked()
{
  QString outputDirectory = QFileDialog::getExistingDirectory(this, tr("select output directory"), ui->lineEditOutputDirectory->text());

  if (!outputDirectory.isEmpty())
  {
    ui->lineEditOutputDirectory->setText(outputDirectory);
  }
}

void MainWindow::on_pushButtonRunUIC_clicked()
{
  QFile uic(ui->lineEditUIC->text());

  if (!uic.exists())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("uic.exe not found\nplease input correct path"));
    messageBox.exec();
    return;
  }

  QDirIterator dirIterator(ui->lineEditInputDirectory->text(), QStringList() << "*.ui");

  int counter = 0;

  while (dirIterator.hasNext())
  {
    QString uiFilePath = dirIterator.next();
    QString headerFilePath = uiFilePath.split('/').last().replace(".ui", ".h").prepend("ui_");

    headerFilePath.prepend(QDir::separator());
    headerFilePath.prepend(ui->lineEditOutputDirectory->text());

    QProcess::execute(ui->lineEditUIC->text(), QStringList() << "-o" << headerFilePath << uiFilePath);
    counter++;
  }

  QMessageBox messageBox;
  messageBox.setText(tr("successfully updated %1 files").arg(counter));
  messageBox.exec();
}

void MainWindow::on_pushButtonRunResourceCompiler_clicked()
{
  QFile rcc(ui->lineEditResourceCompiler->text());

  if (!rcc.exists())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("rcc.exe not found\nplease input correct path"));
    messageBox.exec();
    return;
  }

  QDirIterator dirIterator(ui->lineEditInputDirectory->text(), QStringList() << "*.qrc");

  int counter = 0;

  while (dirIterator.hasNext())
  {
    QString uiFilePath = dirIterator.next();
    QString headerFilePath = uiFilePath.split('/').last().replace(".qrc", ".cpp").prepend("qrc_");

    headerFilePath.prepend(QDir::separator());
    headerFilePath.prepend(ui->lineEditOutputDirectory->text());

    QProcess::execute(ui->lineEditResourceCompiler->text(), QStringList() << "-o" << headerFilePath << uiFilePath);
    counter++;
  }

  QMessageBox messageBox;
  messageBox.setText(tr("successfully updated %1 files").arg(counter));
  messageBox.exec();
}

void MainWindow::on_pushButtonResourceCompiler_clicked()
{
  QString rcc = QFileDialog::getOpenFileName(this, tr("select RCC.exe"), ui->lineEditResourceCompiler->text(), "*.exe");

  if (!rcc.isEmpty())
  {
    ui->lineEditResourceCompiler->setText(rcc);
  }
}
