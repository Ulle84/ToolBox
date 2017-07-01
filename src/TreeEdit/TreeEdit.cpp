#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QInputDialog>
#include <QMenu>
#include <QContextMenuEvent>
#include <QAction>

#include "TreeModel.h"
#include "ProxyModel.h"
#include "TreeItem.h"

#include "TreeEdit.h"
#include "TreeEditUi.h"

TreeEdit::TreeEdit(QWidget* parent) :
  QWidget(parent),
  ui(new TreeEditUi)
{
  setupActions();

  ui->setupUi(this);
  ui->treeView->installEventFilter(this);
}

TreeEdit::~TreeEdit()
{
  delete ui;
}

bool TreeEdit::addNode()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();

  if (!m_proxyModel->insertRow(index.row() + 1, index.parent()))
  {
    return false;
  }

  ui->treeView->selectionModel()->setCurrentIndex(m_proxyModel->index(index.row() + 1, 0, index.parent()), QItemSelectionModel::ClearAndSelect);

  return true;
}

bool TreeEdit::addChildNode()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();

  if (indentation(index) >= m_maxIndentation)
  {
    return false;
  }

  if (!m_proxyModel->insertRow(0, index))
  {
    return false;
  }

  ui->treeView->selectionModel()->setCurrentIndex(m_proxyModel->index(0, 0, index), QItemSelectionModel::ClearAndSelect);

  return true;
}

int TreeEdit::indentation(const QModelIndex& modelIndex)
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

bool TreeEdit::removeNode()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();

  int id = static_cast<TreeItem*>(m_proxyModel->mapToSource(index).internalPointer())->id();

  bool success = m_proxyModel->removeRow(index.row(), index.parent());

  if (success)
  {
    emit itemRemoved(id);
  }

  return success;
}

bool TreeEdit::insertColumn()
{
  bool inputOk;
  QString columnName = QInputDialog::getText(this, tr("input column name"), tr("column name"), QLineEdit::Normal, QString(), &inputOk);

  if (!inputOk || columnName.isEmpty())
  {
    return false;
  }

  int column = ui->treeView->selectionModel()->currentIndex().column();

  bool changed = m_proxyModel->insertColumn(column + 1);

  if (changed)
  {
    m_proxyModel->setHeaderData(column + 1, Qt::Horizontal, columnName, Qt::EditRole);
  }

  return changed;
}

bool TreeEdit::removeColumn()
{
  int column = ui->treeView->selectionModel()->currentIndex().column();
  bool changed = m_proxyModel->removeColumn(column);
  return changed;
}

bool TreeEdit::moveDown()
{
  return m_treeModel->moveDown(selectedIndex());
}

bool TreeEdit::moveUp()
{
  return m_treeModel->moveUp(selectedIndex());
}

bool TreeEdit::moveLeft()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();

  if (indentation(index) <= 0)
  {
    //qDebug() << "moving left not possible - already a top level element";
    return false;
  }

  return m_treeModel->moveLeft(selectedIndex());
}

bool TreeEdit::moveRight()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();

  if (indentation(index) >= m_maxIndentation)
  {
    //qDebug() << "moving right not possible - max indentation level of" << m_maxIndentation << "reached";
    return false;
  }

  return m_treeModel->moveRight(selectedIndex());
}

QByteArray TreeEdit::headerState() const
{
  return ui->treeView->header()->saveState();
}

void TreeEdit::setHeaderState(const QByteArray& headerState)
{
  ui->treeView->header()->restoreState(headerState);
}

void TreeEdit::setMaxIndentation(unsigned int maxIndentation)
{
  m_maxIndentation = maxIndentation;
}

void TreeEdit::setTree(const QJsonObject& tree)
{
  m_lastSelectedId = tree["selectedId"].toInt();
  setupModel(tree);
  selectId(m_lastSelectedId);
}

QJsonObject TreeEdit::toJson()
{
  QJsonObject json = m_treeModel->toJson();
  json["selectedId"] = m_lastSelectedId;
  return json;
}

bool TreeEdit::eventFilter(QObject* obj, QEvent* event)
{
  if (event->type() == QEvent::KeyPress)
  {
    QKeyEvent* e = static_cast<QKeyEvent*>(event);

    if (e->modifiers() & Qt::ControlModifier)
    {
      if (e->key() == Qt::Key_Up)
      {
        moveUp();
      }
      else if (e->key() == Qt::Key_Down)
      {
        moveDown();
      }
      else if (e->key() == Qt::Key_Left)
      {
        moveLeft();
      }
      else if (e->key() == Qt::Key_Right)
      {
        moveRight();
      }
      else
      {
        return QObject::eventFilter(obj, event);
      }
    }
    else
    {
      return QObject::eventFilter(obj, event);
    }

    return true;
  }
  else
  {
    return QObject::eventFilter(obj, event);
  }
}

void TreeEdit::keyPressEvent(QKeyEvent* e)
{
  if (e->modifiers() & Qt::ControlModifier)
  {
    if (e->key() == Qt::Key_N)
    {
      if (e->modifiers() & Qt::ShiftModifier)
        addChildNode();
      else
        addNode();
    }
  }
  else
  {
    if (e->key() == Qt::Key_Delete)
    {
      removeNode();
    }
    else
      QWidget::keyPressEvent(e);
  }
}

void TreeEdit::contextMenuEvent(QContextMenuEvent* event)
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

void TreeEdit::on_lineEditSearch_textChanged(const QString& searchText)
{
  m_proxyModel->setSearchString(searchText);
}

void TreeEdit::onTreeViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
  if (!deselected.isEmpty())
  {
    QModelIndex deselectedIndex = m_proxyModel->mapSelectionToSource(deselected).indexes().first();
  }

  if (!selected.isEmpty())
  {
    QModelIndex selectedIndex = m_proxyModel->mapSelectionToSource(selected).indexes().first();
    m_lastSelectedId = static_cast<TreeItem*>(selectedIndex.internalPointer())->id();
    emit idChanged(m_lastSelectedId);
  }
}

QModelIndex TreeEdit::selectedIndex()
{
  return m_proxyModel->mapToSource(ui->treeView->selectionModel()->currentIndex());
}

void TreeEdit::onResetRequired(int id)
{
  QJsonObject tree = m_treeModel->toJson();

  delete m_treeModel;
  delete m_proxyModel;

  setupModel(tree);
  selectId(id);
}

void TreeEdit::setupModel(const QJsonObject& tree)
{
  m_treeModel = new TreeModel(tree, this);
  m_proxyModel = new ProxyModel(this);
  m_proxyModel->setSourceModel(m_treeModel);

  ui->treeView->setModel(m_proxyModel);
  ui->treeView->expandAll();

  connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &TreeEdit::onTreeViewSelectionChanged);
  connect(m_treeModel, &TreeModel::resetRequired, this, &TreeEdit::onResetRequired);
}

void TreeEdit::setupActions()
{
  m_actionAddNode = new QAction(this);
  m_actionAddNode->setText(QApplication::translate("TreeEdit", "add node", nullptr));
  connect(m_actionAddNode, &QAction::triggered, this, &TreeEdit::addNode);

  m_actionAddChildNode = new QAction(this);
  m_actionAddChildNode->setText(QApplication::translate("TreeEdit", "add child node", nullptr));
  connect(m_actionAddChildNode, &QAction::triggered, this, &TreeEdit::addChildNode);

  m_actionRemoveNode = new QAction(this);
  m_actionRemoveNode->setText(QApplication::translate("TreeEdit", "remove node", nullptr));
  connect(m_actionRemoveNode, &QAction::triggered, this, &TreeEdit::removeNode);

  m_actionInsertColumn = new QAction(this);
  m_actionInsertColumn->setText(QApplication::translate("TreeEdit", "insert column", nullptr));
  connect(m_actionInsertColumn, &QAction::triggered, this, &TreeEdit::insertColumn);

  m_actionRemoveColumn = new QAction(this);
  m_actionRemoveColumn->setText(QApplication::translate("TreeEdit", "remove column", nullptr));
  connect(m_actionRemoveColumn, &QAction::triggered, this, &TreeEdit::removeColumn);

  m_actionMoveDown = new QAction(this);
  m_actionMoveDown->setText(QApplication::translate("TreeEdit", "move down", nullptr));
  connect(m_actionMoveDown, &QAction::triggered, this, &TreeEdit::moveDown);

  m_actionMoveUp = new QAction(this);
  m_actionMoveUp->setText(QApplication::translate("TreeEdit", "move up", nullptr));
  connect(m_actionMoveUp, &QAction::triggered, this, &TreeEdit::moveUp);

  m_actionMoveLeft = new QAction(this);
  m_actionMoveLeft->setText(QApplication::translate("TreeEdit", "move left", nullptr));
  connect(m_actionMoveLeft, &QAction::triggered, this, &TreeEdit::moveLeft);

  m_actionMoveRight = new QAction(this);
  m_actionMoveRight->setText(QApplication::translate("TreeEdit", "move rigth", nullptr));
  connect(m_actionMoveRight, &QAction::triggered, this, &TreeEdit::moveRight);
}

void TreeEdit::selectId(int id)
{
  QModelIndex index = modelIndex(id, QModelIndex());

  if (index.isValid())
  {
    ui->treeView->selectionModel()->setCurrentIndex(m_proxyModel->mapFromSource(index), QItemSelectionModel::ClearAndSelect);
  }
}

QModelIndex TreeEdit::modelIndex(int id, const QModelIndex& parent)
{
  int i = 0;
  QModelIndex index1 = m_treeModel->index(i++, 0, parent);

  while (index1.isValid())
  {
    if (static_cast<TreeItem*>(index1.internalPointer())->id() == id)
    {
      return index1;
    }

    QModelIndex index2 = modelIndex(id, index1);

    if (index2.isValid())
    {
      return index2;
    }

    index1 = m_treeModel->index(i++, 0, parent);
  }

  return QModelIndex();
}

void TreeEdit::getAllIds(QMap<int, QModelIndex>& ids, QModelIndex parent)
{
  int i = 0;
  QModelIndex modelIndex = m_treeModel->index(i++, 0, parent);

  while (modelIndex.isValid())
  {
    ids[static_cast<TreeItem*>(modelIndex.internalPointer())->id()] = modelIndex;
    getAllIds(ids, modelIndex);
    modelIndex = m_treeModel->index(i++, 0, parent);
  }
}
