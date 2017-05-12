#ifndef FILE_H
#define FILE_H

#include <QMap>
#include <QString>
#include <QStringList>

#include "SharedAPI.h"
#include "QtTypeDefs.h"

class SHARED_API File
{
  public:
    File(const QString& path);
    ~File();

    QString toString();
    QStringList toStringList();
    QStringMap toStringMap();

    bool write(const QString& string);
    bool write(const QStringList& stringList);
    bool write(const QStringMap& stringMap);

    void setMapSeperator(const QString& mapSeperator);

    QString directory();
    QString checkSum();
    QString name();

  private:
    QString m_mapSeperator = " --> ";
    QString m_path;
};

#endif