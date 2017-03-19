// created on 2017-03-03 by Ulrich Belitz

//#include <QDir>
#include <QStringList>
#include <QCoreApplication>

#include "Path.h"

namespace Path
{

  QString Path::testFile(const QString& moduleName, const QString& category, const QString& testName, const QString& fileName)
  {
    QStringList stringList;
    stringList << QCoreApplication::applicationDirPath();
    stringList << ".." << "src" << "TestFiles" << moduleName << category << testName << fileName;

    return stringList.join('/');
  }

  QString SHARED_API application()
  {
    return QCoreApplication::applicationDirPath();
  }

  QString SHARED_API configuration()
  {
    QStringList stringList;
    stringList << QCoreApplication::applicationDirPath();
    stringList << ".." << "configuration";

    return stringList.join('/');
  }

  QString SHARED_API configurationFile(const QString& programName, const QString& fileName)
  {
    QStringList stringList;
    stringList << configuration() << programName << fileName;

    return stringList.join('/');
  }

}
