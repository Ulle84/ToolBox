#include <QCoreApplication>

#include "File.h"
#include "Test.h"

namespace Test
{
  bool loadFile(const QString& moduleName, const QString& category, const QString& testName, const QString& fileName, QString& fileContent)
  {
    QStringList stringList;
    stringList << QCoreApplication::applicationDirPath();
    stringList << ".." << "src" << "TestFiles" << moduleName << category << testName << fileName;

    fileContent = File(stringList.join('/')).toString();

    return fileContent.size() != 0;
  }

  bool loadFile(const QString& moduleName, const QString& category, const QString& testName, const QString& fileName, QStringList& fileContent)
  {
    QStringList stringList;
    stringList << QCoreApplication::applicationDirPath();
    stringList << ".." << "src" << "TestFiles" << moduleName << category << testName << fileName;

    fileContent = File(stringList.join('/')).toStringList();

    return fileContent.size() != 0;
  }
}
