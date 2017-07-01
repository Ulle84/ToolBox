#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QColumnView>
#include <QAbstractItemView>
#include <QDebug>
#include <QMenu>
#include <QContextMenuEvent>
#include <QAction>
#include <QInputDialog>

#include "JsonModel.h"
#include "ProxyModel.h"

#include "JsonModelEdit.h"
#include "JsonModelEditUi.h"

JsonModelEdit::JsonModelEdit(QWidget *parent) :
  QWidget(parent),
  ui(new JsonModelEditUi),
  m_proxyModel(new ProxyModel(this))
{
  setupActions();

  ui->setupUi(this);
  m_layout = ui->groupBox->layout();

  setViewType(ViewType::List);
}

JsonModelEdit::~JsonModelEdit()
{
  delete ui;
}

void JsonModelEdit::setModel(JsonModel *model)
{
  m_model = model;
  m_proxyModel->setSourceModel(m_model);
  if(view)
    view->setModel(model);
}

JsonModel *JsonModelEdit::model()
{
  return m_model;
}

void JsonModelEdit::setViewType(JsonModelEdit::ViewType viewType)
{
  if (view)
  {
    QLayoutItem* layoutItem = m_layout->takeAt(m_layout->count() - 1);
    if (layoutItem)
    {
      QWidget* widget = layoutItem->widget();

      if (widget)
        delete widget;

      delete layoutItem;
    }
    view = nullptr;
  }

  if (viewType == ViewType::List)
  {
    view = new QListView;
  }
  else if (viewType == ViewType::Table)
  {
    view = new QTableView;
  }
  else if (viewType == ViewType::Tree)
  {
    view = new QTreeView;
  }
  else if (viewType == ViewType::Columns)
  {
    view = new QColumnView;
  }

  if (view)
    m_layout->addWidget(view);
}

void JsonModelEdit::setMaxIndentation(unsigned int maxIndentation)
{
  m_maxIndentation = maxIndentation;
}

bool JsonModelEdit::addNode()
{
  QModelIndex index = view->selectionModel()->currentIndex();

  if (!m_proxyModel->insertRow(index.row() + 1, index.parent()))
  {
    return false;
  }

  view->selectionModel()->setCurrentIndex(m_proxyModel->index(index.row() + 1, 0, index.parent()), QItemSelectionModel::ClearAndSelect);

  return true;
}

bool JsonModelEdit::addChildNode()
{
  QModelIndex index = view->selectionModel()->currentIndex();

  if (indentation(index) >= m_maxIndentation)
  {
    return false;
  }

  if (!m_proxyModel->insertRow(0, index))
  {
    return false;
  }

  view->selectionModel()->setCurrentIndex(m_proxyModel->index(0, 0, index), QItemSelectionModel::ClearAndSelect);

  return true;
}

int JsonModelEdit::indentation(const QModelIndex& modelIndex)
{
  int indent = 0;
  QModelIndex parent = modelIndex.parent();

  while (parent.isValid())
  {
    indent++;
    parent = parent.parent();
  }

  return indent;
}

bool JsonModelEdit::removeNode()
{
  QModelIndex index = view->selectionModel()->currentIndex();

  // TODO ID Handling
  //int id = static_cast<TreeItem*>(m_proxyModel->mapToSource(index).internalPointer())->id();

  bool success = m_proxyModel->removeRow(index.row(), index.parent());

  //if (success)
  //{
  //  emit itemRemoved(id);
  //}

  return success;
}

bool JsonModelEdit::insertColumn()
{
  bool inputOk;
  QString columnName = QInputDialog::getText(this, tr("input column name"), tr("column name"), QLineEdit::Normal, QString(), &inputOk);

  if (!inputOk || columnName.isEmpty())
  {
    return false;
  }

  int column = view->selectionModel()->currentIndex().column();

  bool changed = m_proxyModel->insertColumn(column + 1);

  if (changed)
  {
    m_proxyModel->setHeaderData(column + 1, Qt::Horizontal, columnName, Qt::EditRole);
  }

  return changed;
}

bool JsonModelEdit::removeColumn()
{
  int column = view->selectionModel()->currentIndex().column();
  bool changed = m_proxyModel->removeColumn(column);
  return changed;
}

bool JsonModelEdit::moveDown()
{
  return true; // TODO implement this method
  //return m_treeModel->moveDown(selectedIndex());
}

bool JsonModelEdit::moveUp()
{
  return true; // TODO implement this method
  //return m_treeModel->moveUp(selectedIndex());
}

bool JsonModelEdit::moveLeft()
{
  return true; // TODO implement this method

  //QModelIndex index = ui->treeView->selectionModel()->currentIndex();
  //
  //if (indentation(index) <= 0)
  //{
  //  //qDebug() << "moving left not possible - already a top level element";
  //  return false;
  //}
  //
  //return m_treeModel->moveLeft(selectedIndex());
}

bool JsonModelEdit::moveRight()
{
  return true; // TODO implement this method

  //QModelIndex index = ui->treeView->selectionModel()->currentIndex();
  //
  //if (indentation(index) >= m_maxIndentation)
  //{
  //  //qDebug() << "moving right not possible - max indentation level of" << m_maxIndentation << "reached";
  //  return false;
  //}
  //
  //return m_treeModel->moveRight(selectedIndex());
}

void JsonModelEdit::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu menu(this);
    menu.addAction(m_actionAddNode);
    menu.addAction(m_actionAddChildNode);
    menu.addAction(m_actionRemoveNode);
    menu.addAction(m_actionInsertColumn);
    menu.addAction(m_actionRemoveColumn);
    menu.addAction(m_actionMoveDown);
    menu.addAction(m_actionMoveUp);
    menu.addAction(m_actionMoveLeft);
    menu.addAction(m_actionMoveRight);
    menu.exec(event->globalPos());
}

void JsonModelEdit::setupActions()
{
  m_actionAddNode = new QAction(this);
  m_actionAddNode->setText(QApplication::translate("JsonModelEdit", "add node", nullptr));
  connect(m_actionAddNode, &QAction::triggered, this, &JsonModelEdit::addNode);

  m_actionAddChildNode = new QAction(this);
  m_actionAddChildNode->setText(QApplication::translate("JsonModelEdit", "add child node", nullptr));
  connect(m_actionAddChildNode, &QAction::triggered, this, &JsonModelEdit::addChildNode);

  m_actionRemoveNode = new QAction(this);
  m_actionRemoveNode->setText(QApplication::translate("JsonModelEdit", "remove node", nullptr));
  connect(m_actionRemoveNode, &QAction::triggered, this, &JsonModelEdit::removeNode);

  m_actionInsertColumn = new QAction(this);
  m_actionInsertColumn->setText(QApplication::translate("JsonModelEdit", "insert column", nullptr));
  connect(m_actionInsertColumn, &QAction::triggered, this, &JsonModelEdit::insertColumn);

  m_actionRemoveColumn = new QAction(this);
  m_actionRemoveColumn->setText(QApplication::translate("JsonModelEdit", "remove column", nullptr));
  connect(m_actionRemoveColumn, &QAction::triggered, this, &JsonModelEdit::removeColumn);

  m_actionMoveDown = new QAction(this);
  m_actionMoveDown->setText(QApplication::translate("JsonModelEdit", "move down", nullptr));
  connect(m_actionMoveDown, &QAction::triggered, this, &JsonModelEdit::moveDown);

  m_actionMoveUp = new QAction(this);
  m_actionMoveUp->setText(QApplication::translate("JsonModelEdit", "move up", nullptr));
  connect(m_actionMoveUp, &QAction::triggered, this, &JsonModelEdit::moveUp);

  m_actionMoveLeft = new QAction(this);
  m_actionMoveLeft->setText(QApplication::translate("JsonModelEdit", "move left", nullptr));
  connect(m_actionMoveLeft, &QAction::triggered, this, &JsonModelEdit::moveLeft);

  m_actionMoveRight = new QAction(this);
  m_actionMoveRight->setText(QApplication::translate("JsonModelEdit", "move rigth", nullptr));
  connect(m_actionMoveRight, &QAction::triggered, this, &JsonModelEdit::moveRight);
}
