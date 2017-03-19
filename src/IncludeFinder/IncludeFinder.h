#ifndef INCLUDEFINDER_H
#define INCLUDEFINDER_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "CommentHandler.h"

class IncludeFinder : public QObject
{
    Q_OBJECT

  public:
    IncludeFinder();
    QStringList files(const QStringList& directories, const QStringList& includes);

  signals:
    void notifyProgress(const QString& progress);

  private:
    void parsePotentialFiles(const QStringList& directories);

    QStringList m_extensions;
    QStringList m_potentialFiles;

    CommentHandler m_commentHandler;
};

#endif // INCLUDEFINDER_H