#include <QVariant>
#include <QJsonObject>
#include <QDebug>

#include "JsonModel.h"

JsonModel::JsonModel(QObject *parent) :
  QStandardItemModel(parent)
{

}

bool JsonModel::setContent(const QJsonArray& content, QStandardItem *parentItem)
{
  for (int r = 0; r < content.count(); ++r)
  {
    QJsonObject object = content[r].toObject();
    if (object.contains("data"))
    {
      QJsonArray columns = object["data"].toArray();
      QList<QStandardItem*> items;
      for (int c = 0; c < columns.count(); ++c)
      {
        items.append(new QStandardItem(columns[c].toString()));
      }

      if (parentItem)
        parentItem->appendRow(items);
      else
        appendRow(items);

      if (object.contains("children"))
      {
        setContent(object["children"].toArray(), items.first());
      }
    }
    else
    {
      return false;
    }
  }
  return true;
}

QJsonArray JsonModel::content(QModelIndex parentIndex)
{
  QJsonArray result;

  for (int r = 0; r < rowCount(parentIndex); ++r)
  {
    QJsonArray columns;

    for (int c = 0; c < columnCount(parentIndex); ++c)
    {
      QVariant variant = data(index(r, c, parentIndex));

      // TODO support for all types of JsonValues
      if (variant.isValid())
      {
        columns.append(variant.toString());
      }
      else
      {
        columns.append(QJsonValue()); // null
      }
    }

    QJsonObject object;
    object["data"] = columns;

    QModelIndex modelIndex = index(r, 0, parentIndex);

    if (hasChildren(modelIndex))
    {
      object["children"] = content(modelIndex);
    }

    result.append(object);
  }

  return result;
}
