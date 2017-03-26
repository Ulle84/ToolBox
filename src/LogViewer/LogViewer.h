#ifndef LOGVIEWER_H
#define LOGVIEWER_H

#include <QAbstractTableModel>
#include <QList>
#include <QDate>

#include "LogViewerEntry.h"

class LogViewer : public QAbstractTableModel
{
    Q_OBJECT

  public:
    LogViewer(QObject* parent);

    // Implementation of QAbstractTableModel
    int rowCount(const QModelIndex& parent = QModelIndex()) const ;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex& index) const ;

    void readFromFile(const QString& fileName);
    int numberOfEntries();

  private:
    QList<LogViewerEntry> m_entries;
};

#endif