#include <QDebug>

#include "LogViewer.h"
#include "File.h"
#include "Path.h"

LogViewer::LogViewer(QObject* parent) :
  QAbstractTableModel(parent)
{
}

int LogViewer::rowCount(const QModelIndex& parent) const
{
  return m_entries.length();
}

int LogViewer::columnCount(const QModelIndex& parent) const
{
  return LogViewerEntry::numberOfAttributes();
}

QVariant LogViewer::data(const QModelIndex& index, int role) const
{
  if (role == Qt::DisplayRole)
  {
	  return m_entries[index.row()].data(index.column());

    
  }

  return QVariant();
}

QVariant LogViewer::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal)
    {
      return LogViewerEntry::header(section);
    }
  }

  return QVariant();
}

bool LogViewer::setData(const QModelIndex& index, const QVariant& value, int role)
{
  return true;
}

Qt::ItemFlags LogViewer::flags(const QModelIndex& index) const
{
  return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

// TODO should be in a seperate class "LogViewerReader"
void LogViewer::readFromFile(const QString& fileName)
{
  QStringList fileContent = File(fileName).toStringList();

  QString dateTime;
  QString level;
  QString threadNumber;
  QString name;
  QString message;

  for (auto it = fileContent.begin(); it != fileContent.end(); ++it)
  {

	 m_entries.append(LogViewerEntry(*it));
      
    
  }
}

int LogViewer::numberOfEntries()
{
  return m_entries.length();
}
