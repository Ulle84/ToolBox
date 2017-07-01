#include <QSettings>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new MainWindowUi)
{
  ui->setupUi(this);

  m_settings = new QSettings("ScientaOmicron", "SvnUpdateFilter", this);

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

void MainWindow::on_plainTextEditInput_textChanged()
{
  QStringList input = ui->plainTextEditInput->toPlainText().split('\n');

  QStringList filteredLines;
  filteredLines << "Command: Update";
  filteredLines << "Updating: ";
  filteredLines << "External: ";
  filteredLines << "Completed: ";

  QStringList output;

  for (auto it = input.begin(); it != input.end(); ++it)
  {
    bool appendLine = true;

    QString trimmed = it->trimmed();

    if (trimmed.isEmpty())
    {
      continue;
    }

    for (auto it2 = filteredLines.begin(); it2 != filteredLines.end(); ++it2)
    {
      if (trimmed.startsWith(*it2))
      {
        appendLine = false;
        break;
      }
    }

    if (appendLine)
    {
      output.append(trimmed);
    }
  }

  if (output.isEmpty())
  {
    ui->plainTextEditOutput->setPlainText(tr("no relevant changes"));
  }
  else
  {
    ui->plainTextEditOutput->setPlainText(output.join('\n'));
  }
}
