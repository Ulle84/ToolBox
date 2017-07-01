// created on 2017-04-01 by Ulrich Belitz

#include <QFileDialog>
#include <QDir>

#include "PathList.h"
#include "PathListUi.h"

PathList::PathList(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::PathList)
{
  ui->setupUi(this);
}

PathList::~PathList()
{
  delete ui;
}

QStringList PathList::paths()
{
	QStringList list;

	QStringList text = ui->plainTextEdit->toPlainText().split('\n', QString::SkipEmptyParts);

	for (auto it : text)
	{
		// TODO use QFileInfo?

		if (QDir(it).exists())
		{
			list.append(it);
			continue;
		}
			

		if (QFile(it).exists())
			list.append(it);
	}
	return list;
}

QStringList PathList::directories()
{
	QStringList list;

	QStringList text = ui->plainTextEdit->toPlainText().split('\n', QString::SkipEmptyParts);

	for (auto it : text)
	{
		if (QDir(it).exists())
		{
			list.append(it);
			
		}
	}
	return list;
}

QStringList PathList::files()
{
	QStringList list;

	QStringList text = ui->plainTextEdit->toPlainText().split('\n', QString::SkipEmptyParts);

	for (auto it : text)
	{
		


		if (QFile(it).exists())
			list.append(it);
	}
	return list;
}

void PathList::on_pushButtonAddDirectory_clicked()
{

	QString path = QFileDialog::getExistingDirectory(this, tr("select directory"), m_lastSelectedPath);
	if (!path.isEmpty())
	{
		m_lastSelectedPath = path;
		ui->plainTextEdit->appendPlainText(path);
	}
}

void PathList::on_pushButtonAddFiles_clicked()
{
	QStringList path = QFileDialog::getOpenFileNames(this, tr("select files"), m_lastSelectedPath);
	if (!path.isEmpty())
	{
		m_lastSelectedPath = path.first();

		for (auto it : path)
			ui->plainTextEdit->appendPlainText(it);
	}
}

void PathList::on_pushButtonClearList_clicked()
{
	ui->plainTextEdit->clear();
}
