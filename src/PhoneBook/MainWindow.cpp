#include <QDebug>
#include <QSettings>
#include <QSortFilterProxyModel>

#include "MainWindow.h"
#include "PhoneBook.h"
#include "ProxyModel.h"
#include "MainWindowUi.h"

#include <QMap>
#include <QIcon>

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  setWindowIcon(QIcon(":/images/logo.png"));

  m_settings = new QSettings("Ulle", "PhoneBook", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  m_phoneBook = new PhoneBook(this);

  m_proxyModel = new ProxyModel(this);

  m_proxyModel->setSourceModel(m_phoneBook);

  ui->tableView->setModel(m_proxyModel);

  ui->statusBar->showMessage(QString("%1 entries - last update: %2").arg(m_phoneBook->numberOfEntries()).arg(m_phoneBook->lastUpdate().toString("yyyy-MM-dd")));
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());

  delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString& text)
{
  m_proxyModel->setSearchString(text);
}