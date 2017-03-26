#include <QDebug>
#include <QSettings>
#include <QSortFilterProxyModel>
#include <QFileDialog>

#include "MainWindow.h"
#include "LogViewer.h"
#include "ProxyModel.h"
#include "ui_MainWindow.h"

#include <QMap>
#include <QIcon>

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->pathSelector->setLabelText(tr("log file"));
  ui->pathSelector->setButtonText(tr("choose log file"));
  ui->pathSelector->setPathType(PathSelector::PathType::File);

  m_settings = new QSettings("Ulle", "LogViewer", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  ui->pathSelector->setPath(m_settings->value("path").toString());
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("path", ui->pathSelector->path());

  delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString& text)
{
  m_proxyModel->setSearchString(text);
}

void MainWindow::on_pathSelector_pathChanged(const QString& path)
{
	QFile file(path);
	if (!file.exists())
		return;

	delete m_logViewer;
	delete m_proxyModel; 

	m_logViewer = new LogViewer(this);

	m_logViewer->readFromFile(path);

	m_proxyModel = new ProxyModel(this);

	m_proxyModel->setSourceModel(m_logViewer);

	ui->tableView->setModel(m_proxyModel);
	ui->tableView->resizeColumnsToContents();
}
