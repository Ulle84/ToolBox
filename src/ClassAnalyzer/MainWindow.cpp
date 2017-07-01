#include <QFileDialog>
#include <QSettings>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "ClassAnalyzer", this);

  if (m_settings->contains("lastSelectedDirectory"))
  {
    m_lastSelectedDirectory = m_settings->value("lastSelectedDirectory").toString();
  }

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("lastSelectedDirectory", m_lastSelectedDirectory);
  m_settings->setValue("geometry", geometry());
  delete ui;
}

void MainWindow::on_pushButtonParseFolder_clicked()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Select folder.."), m_lastSelectedDirectory);

  if (directory.isEmpty())
  {
    return;
  }

  m_lastSelectedDirectory = directory;

  m_classAnalyzer.parseFolder(directory);

  updateResult();
}

void MainWindow::on_pushButtonParseVernissage_clicked()
{
  QStringList folders;
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Base/DataTypes/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Base/Exceptions/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Base/Incl/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Base/Math/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Base/Monitoring/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Base/ServiceBus/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Base/Socket/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Base/SystemConfig/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Base/Thread/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Base/Utilities/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Base/Value/");

  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Foundation/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Incl/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Main/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/PlugIns/");
  folders.append("D:/CMake/VernissageKit/trunk/Vernissage/src/Store/");
  m_classAnalyzer.parseFolders(folders);

  updateResult();
}

void MainWindow::updateResult()
{
  ui->plainTextEditResult->setPlainText(m_classAnalyzer.allClasses());

  ui->plainTextEditResult->appendPlainText(m_classAnalyzer.filesWithMoreThanOneClassDeclaration());
}
