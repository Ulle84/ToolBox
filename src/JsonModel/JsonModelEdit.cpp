#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QColumnView>
#include <QAbstractItemView>
#include <QDebug>

#include <JsonModel.h>

#include "JsonModelEdit.h"
#include "ui_JsonModelEdit.h"

JsonModelEdit::JsonModelEdit(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::JsonModelEdit)
{
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
