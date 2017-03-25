#include <QSettings>
#include <QFileDialog>

#include "File.h"
#include "Directory.h"
#include "Path.h"
#include "QStringEx.h"

#include "CodeDuplicator.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->pathSelector, &PathSelector::pathChanged, this, &MainWindow::onPathChanged);

  setWindowTitle("CodeDuplicator");

  m_settings = new QSettings("Ulle", "CodeDuplicator", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  ui->pathSelector->setPath(m_settings->value("path").toString());
  ui->lineEditDuplicate->setText(m_settings->value("duplicate").toString());

  
}

MainWindow::~MainWindow()
{
	m_settings->setValue("geometry", geometry());
	m_settings->setValue("path", ui->pathSelector->path());
	m_settings->setValue("duplicate", ui->lineEditDuplicate->text());

  delete ui;
}

void MainWindow::on_pushButtonDuplicate_clicked()
{
	QString sourcePath = ui->pathSelector->path();

	if (sourcePath.isEmpty())
		return;

	if (!Directory::exists(sourcePath))
		return;

	QString sourceName = ui->lineEditOriginal->text();
	QString destinationName = ui->lineEditDuplicate->text();

	if (sourceName.isEmpty() || destinationName.isEmpty())
		return;

	QString destinationPath = Directory::moveDown(Directory::moveUp(sourcePath), destinationName);

	QFileInfo fileInfo(destinationPath);

	if (fileInfo.exists())
		return;
	
	bool success = process(sourcePath, destinationPath, sourceName, destinationName, destinationPath.length());
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
		foreach(const QString &fileName, fileNames)
		{

			QString newSourceFilePath = source + QLatin1Char('/') + fileName;
			QString newDestinationFilePath = destination + QLatin1Char('/') + fileName;

			newDestinationFilePath = QStringEx::replace(newDestinationFilePath, sourceName, destinationName, offsetIndex);

			if (!process(newSourceFilePath, newDestinationFilePath, sourceName, destinationName, offsetIndex))
				return false;
		}
	}
	else
	{
		if (!QFile::copy(source, destination))
			return false;
		else
		{
			// change content inside file
			QString fileContent = File::fileToString(destination);
			fileContent.replace(sourceName, destinationName);
			fileContent.replace(sourceName.toUpper(), destinationName.toUpper());
			fileContent.replace(QStringEx::lowercaseFirstLetter(sourceName), QStringEx::lowercaseFirstLetter(destinationName));
			File::stringToFile(fileContent, destination);
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
