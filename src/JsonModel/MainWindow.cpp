#include <QJsonDocument>

#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  JsonModel* jsonModel = new JsonModel(this);

  setTestContent(jsonModel);

  QJsonArray content = jsonModel->content();

  QJsonDocument jsonDocument(content);
  //ui->plainTextEdit->setPlainText(jsonDocument.toJson());

  JsonModel* jsonModel2 = new JsonModel(this);
  jsonModel2->setContent(content);

  ui->listView->setModel(jsonModel);
  //ui->listView_2->setModel(jsonModel2);

  ui->tableView->setModel(jsonModel);
  //ui->tableView_2->setModel(jsonModel2);

  ui->treeView->setModel(jsonModel);
  //ui->treeView_2->setModel(jsonModel2);

  ui->widget->setViewType(JsonModelEdit::ViewType::Tree);
  ui->widget->setModel(jsonModel);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setTestContent(JsonModel *model)
{
  model->appendRow(new QStandardItem("row one"));
  model->appendRow(new QStandardItem("row two"));
  model->appendRow(QList<QStandardItem*>() << new QStandardItem("row three") << new QStandardItem("row three 2"));

  QStandardItem* parentItem = new QStandardItem("parent");
  model->appendRow(parentItem);

  parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem("child") << new QStandardItem("child 2") << new QStandardItem("child 3"));
  parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem("childb") << new QStandardItem("childb 2") << new QStandardItem("childb 3"));

  QStandardItem* parentItem2 = new QStandardItem("parent2");

  parentItem->appendRow(parentItem2);
  parentItem2->appendRow(QList<QStandardItem*>() << new QStandardItem("c child") << new QStandardItem("c child 2") << new QStandardItem("c child 3"));
  parentItem2->appendRow(QList<QStandardItem*>() << new QStandardItem("c childb") << new QStandardItem("c childb 2") << new QStandardItem("c childb 3"));



  model->appendRow(QList<QStandardItem*>() << new QStandardItem("row four") << new QStandardItem("row four 2"));

  for (int i = 0; i < model->columnCount(); ++i)
    model->setHeaderData(i, Qt::Horizontal, QString("column %1").arg(i));

  for (int i = 0; i < model->rowCount(); ++i)
    model->setHeaderData(i, Qt::Vertical, QString("row %1").arg(i));
}
