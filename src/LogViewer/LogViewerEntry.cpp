#include <QVariant>

#include "LogViewerEntry.h"

const QStringList LogViewerEntry::m_headers = QStringList() << "date" << "time" << "level" << "thread id" << "name" << "message";

LogViewerEntry::LogViewerEntry()
{
}

LogViewerEntry::LogViewerEntry(const QString& logContent)
{
	QStringList splitted = logContent.split(' ');
	if (splitted.size() >= 5)
	{
		m_date = splitted.takeAt(0);
		m_time= splitted.takeAt(0);
		m_level = splitted.takeAt(0); // TODO translation method I -> '3 - Information' etc
		m_threadNumber = splitted.takeAt(0);
		QString name = splitted.takeAt(0);
		m_name = name.left(name.length() - 1);
		m_message = splitted.join(' ');
	}
		
}

int LogViewerEntry::numberOfAttributes()
{
  return m_headers.length();
}

QString LogViewerEntry::header(int section)
{
  return m_headers.at(section);
}

QVariant LogViewerEntry::data(int column) const
{
	switch (column)
	{
		// TODO use enum
	case 0:
		return m_date; 
	case 1:
		return m_time; 
	case 2:
		return m_level;
	case 3:
		return m_threadNumber;
	case 4:
		return m_name;
	case 5:
		return m_message;
	}
	return QVariant();
}

void LogViewerEntry::setData(const QVariant& data, int column)
{
	switch (column)
	{
		// TODO use enum
	case 0:
		m_date = data.toString();
		break;
	case 1:
		m_time = data.toString();
		break;
	case 2:
		m_level = data.toString();
		break;
	case 3:
		m_threadNumber = data.toString();
		break;
	case 4:
		m_name = data.toString();
		break;
	case 5:
		m_message = data.toString();
		break;
	}
}
