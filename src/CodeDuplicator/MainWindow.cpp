#include <QSettings>
#include <QFileDialog>

#include "File.h"
#include "Directory.h"
#include "Path.h"
#include "QStringEx.h"

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  setWindowTitle("CodeDuplicator");

  m_settings = new QSettings("Ulle", "CodeDuplicator", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  ui->lineEditDuplicate->setText(m_settings->value("duplicate").toString());
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("duplicate", ui->lineEditDuplicate->text());

  delete ui;
}

void MainWindow::on_pushButtonDuplicate_clicked()
{
  QStringList directories = ui->pathList->directories();
  QStringList files = ui->pathList->files();

  QString sourceName = ui->lineEditOriginal->text();
  QString destinationName = ui->lineEditDuplicate->text();

  if (sourceName.isEmpty() || destinationName.isEmpty())
  {
    return;
  }

  bool success = true;

  for (auto it : directories)
  {
    QString sourcePath = it;

    QString destinationPath = Directory::moveDown(Directory::moveUp(sourcePath), destinationName);

    QFileInfo fileInfo(destinationPath);

    if (fileInfo.exists())
    {
      ui->logConsole->error(tr("directory \"%1\" already exists").arg(destinationName));
      //ui->statusBar->showMessage(tr("directory %1 already exists").arg(destinationName));
      return;
    }

    success &= process(sourcePath, destinationPath, sourceName, destinationName, destinationPath.length());
  }

  for (auto it : files)
  {
    QString sourcePath = it;

    QString destinationPath = Path::exchangeFileName(sourcePath, sourceName, destinationName);

    if (destinationPath.isEmpty())
    {
      continue;
    }

    QFileInfo fileInfo(destinationPath);

    if (fileInfo.exists())
    {
      ui->logConsole->error(tr("file \"%1\" already exists").arg(destinationName));
      //ui->statusBar->showMessage(tr("file %1 already exists").arg(destinationName));
      return;
    }

    success &= process(sourcePath, destinationPath, sourceName, destinationName, destinationPath.length());
  }

  if (success)
  {
    ui->logConsole->success(tr("duplicated \"%1\" to \"%2\"").arg(sourceName).arg(destinationName));
    //ui->statusBar->showMessage(tr("succesfully duplicated %1 to %2").arg(sourceName).arg(destinationName));
  }

  else
  {
    ui->logConsole->error(tr("duplication failed"));
    //ui->statusBar->showMessage(tr("duplication failed"));
  }
}

void MainWindow::onPathChanged(const QString& path)
{
  ui->lineEditOriginal->setText(Directory::name(path));
}

bool MainWindow::process(const QString& source, const QString& destination, const QString& sourceName, const QString& destinationName, uint offsetIndex)
{
  QFileInfo srcFileInfo(source);

  if (srcFileInfo.isDir())
  {
    QDir targetDir(destination);
    targetDir.cdUp();

    if (!targetDir.mkdir(QFileInfo(destination).fileName()))
    {
      return false;
    }

    QDir sourceDir(source);
    QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

    foreach (const QString& fileName, fileNames)
    {
      QString newSourceFilePath = source + QLatin1Char('/') + fileName;
      QString newDestinationFilePath = destination + QLatin1Char('/') + fileName;

      newDestinationFilePath = QStringEx::replace(newDestinationFilePath, sourceName, destinationName, offsetIndex);

      if (!process(newSourceFilePath, newDestinationFilePath, sourceName, destinationName, offsetIndex))
      {
        return false;
      }
    }
  }
  else
  {
    if (!QFile::copy(source, destination))
    {
      return false;
    }
    else
    {
      QStringList fileExtensionsToChange;
      fileExtensionsToChange << "h" << "hpp" << "cpp" << "ui" << "qrc" << "txt" << "md";

      if (fileExtensionsToChange.contains(Path::fileNameExtension(destination)))
      {
        QString fileContent = File(destination).toString();
        fileContent.replace(sourceName, destinationName);
        fileContent.replace(sourceName.toUpper(), destinationName.toUpper());
        fileContent.replace(QStringEx::lowercaseFirstLetter(sourceName), QStringEx::lowercaseFirstLetter(destinationName));
        File(destination).write(fileContent);
      }
    }
  }

  return true;
}

void MainWindow::changeFilePath(QString& filePath, const QString& newFileName)
{
  QString directory = Path::directory(filePath);
  QString extension = Path::fileNameExtension(filePath);

  filePath = directory + '/' + newFileName + '.' + extension;
}
