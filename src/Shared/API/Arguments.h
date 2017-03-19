// created on 2017-01-24 by Ulrich Belitz

#ifndef COMMS_ARGUMENTS_H
#define COMMS_ARGUMENTS_H

#include <QMap>
#include <QString>
#include <QStringList>

#include "SharedAPI.h"

// TODO create test
// TODO support additional parsing of options files

class SHARED_API Arguments
{
  public:
    Arguments();
    Arguments(int argc, char* argv[]);
    ~Arguments();

    void processArguments(int argc, char* argv[]);

    QString argument(const QString& name);
    QStringList arguments(const QString& name);

    bool isOptionSet(const QString& name);

    void clear();

  private:
    QMap<QString, QStringList> m_arguments;
};

#endif