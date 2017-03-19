#ifndef CMAKEHELPER_H
#define CMAKEHELPER_H

#include <QObject>
#include <QString>
#include <QStringList>

class CMakeHelper : public QObject
{
    Q_OBJECT

  public:
    CMakeHelper();
    QStringList files(const QStringList& directories, const QString& searchString);

  signals:
    void notifyProgress(const QString& progress);

  private:
    void parsePotentialFiles(const QStringList& directories);

    QStringList m_potentialFiles;
};

#endif