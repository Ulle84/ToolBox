#ifndef JSONMODEL_H
#define JSONMODEL_H

#include <QJsonArray>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QModelIndex>

class JsonModel : public QStandardItemModel
{
public:
  JsonModel(QObject *parent = 0);

  bool setContent(const QJsonArray& content, QStandardItem* parentItem = nullptr);
  QJsonArray content(QModelIndex parentIndex = QModelIndex());
};

#endif
