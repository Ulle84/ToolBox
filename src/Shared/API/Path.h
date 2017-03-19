// created on 2017-03-03 by Ulrich Belitz

#ifndef PATH_H
#define PATH_H

#include <QString>
#include <QStringList>

#include "SharedAPI.h"

namespace Path
{
  QString SHARED_API application();
  QString SHARED_API configuration();
  QString SHARED_API configurationFile(const QString& programName, const QString& fileName);
  QString SHARED_API testFile(const QString& moduleName, const QString& category, const QString& testName, const QString& fileName);
}

#endif