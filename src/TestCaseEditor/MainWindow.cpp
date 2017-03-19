// created on 2017-01-12 by Ulrich Belitz

#include <QSettings>
#include <QDirIterator>
#include <QDebug>

#include "File.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("Test Case Editor");
  setWindowIcon(QIcon(":/images/logo.png"));

  m_settings = new QSettings("Ulle", "TestCaseEditor", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  ui->lineEditDirectory->setText(m_settings->value("selectedDirectory").toString());
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("selectedDirectory", ui->lineEditDirectory->text());

  delete ui;
}

void MainWindow::on_pushButtonAdd_clicked()
{
  // TODO show dialog and create testCase_input.txt and testCase_output.txt
}

void MainWindow::on_pushButtonDelete_clicked()
{
  // TODO delete testCase_input.txt and testCase_output.txt
}

void MainWindow::on_lineEditDirectory_returnPressed()
{
  ui->comboBoxTestCase->clear();

  QDirIterator dirIterator(ui->lineEditDirectory->text());

  QStringList allFileNames;

  while (dirIterator.hasNext())
  {
    allFileNames.append(dirIterator.next());
  }

  for (auto& it : allFileNames)
  {
    if (it.endsWith(m_inputFileNameEnd))
    {
      QString testCaseName = it.mid(it.lastIndexOf('/') + 1, it.size() - it.lastIndexOf('_'));

      for (auto& it2 : allFileNames)
      {
        if (it2.endsWith(testCaseName + m_outputFileNameEnd))
        {
          ui->comboBoxTestCase->addItem(testCaseName);
          break;
        }
      }
    }
  }
}

void MainWindow::on_comboBoxTestCase_currentIndexChanged(const QString& text)
{
  ui->textEditInput->setPlainText(File::fileToString(ui->lineEditDirectory->text() + text + m_inputFileNameEnd));
  ui->textEditOutput->setPlainText(File::fileToString(ui->lineEditDirectory->text() + text + m_outputFileNameEnd));
}
