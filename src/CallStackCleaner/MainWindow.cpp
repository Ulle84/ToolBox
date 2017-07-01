// created on 2017-01-04 by Ulrich Belitz

#include <QClipboard>
#include <QString>
#include <QSettings>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("CallStackCleaner");
  setWindowIcon(QIcon(":/images/logo.png"));

  m_settings = new QSettings("Ulle", "CallStackCleaner", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  ui->checkBoxRevertOrder->setChecked(m_settings->value("revertCallStack").toBool());
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("revertCallStack", ui->checkBoxRevertOrder->isChecked());

  delete ui;
}

void MainWindow::on_pushButtonCleanCallStack_clicked()
{
  QStringList output;
  QString callStack = QApplication::clipboard()->text();

  QStringList lines = callStack.split('\n', QString::SkipEmptyParts);

  for (auto& it : lines)
  {
    QStringList tokens = it.split('\t');

    if (tokens.size() == 3)
    {
      if (tokens[1] != "[External Code]")
      {
        tokens[1].replace('!', ' ');
        tokens[1].replace(" &", "&");
        tokens[1].replace(" *", "*");
        output.append(tokens[1]);
      }
    }
    else
    {
      ui->statusBar->showMessage(tr("no call stack in clipboard"), m_messageShowTimeMilliSeconds);
      return;
    }
  }

  if (ui->checkBoxRevertOrder->isChecked())
  {
    std::reverse(output.begin(), output.end());
  }

  QApplication::clipboard()->setText(output.join('\n'));

  ui->statusBar->showMessage(tr("call stack cleaned"), m_messageShowTimeMilliSeconds);
}
