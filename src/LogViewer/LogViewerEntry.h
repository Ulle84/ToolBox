#ifndef LOGVIEWERENTRY_H
#define LOGVIEWERENTRY_H

#include <QString>
#include <QStringList>

class LogViewerEntry
{
  public:
	  LogViewerEntry(const QString& logContent);
    LogViewerEntry();	

    static int numberOfAttributes();
    static QString header(int section);

	QVariant data(int column) const;
	void setData(const QVariant& data, int column);

  private:
    static const QStringList m_headers;

	QString m_date;
	QString m_time;
    QString m_level;
    QString m_threadNumber;
    QString m_name;
    QString m_message;
};

#endif // LOGVIEWERENTRY_H