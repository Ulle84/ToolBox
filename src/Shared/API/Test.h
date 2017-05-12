#ifndef TEST_H
#define TEST_H

#include <QString>
#include <QStringList>

#include "SharedAPI.h"

namespace Test
{
  bool SHARED_API loadFile(const QString& moduleName, const QString& category, const QString& testName, const QString& fileName, QString& fileContent);
  bool SHARED_API loadFile(const QString& moduleName, const QString& category, const QString& testName, const QString& fileName, QStringList& fileContent);
}

#endif