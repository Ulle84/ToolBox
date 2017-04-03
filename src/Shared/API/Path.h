// created on 2017-03-03 by Ulrich Belitz

#ifndef PATH_H
#define PATH_H

#include <QString>
#include <QStringList>

#include "SharedAPI.h"

namespace Path
{
	// TODO rename to applicationDirectory and configurationDirectory
  QString SHARED_API application();
  QString SHARED_API configuration();
  QString SHARED_API configurationFile(const QString& programName, const QString& fileName);
  QString SHARED_API testFile(const QString& moduleName, const QString& category, const QString& testName, const QString& fileName);
  QString SHARED_API portableProgram(const QString& programName);

  QString SHARED_API directory(const QString& filePath);
  QString SHARED_API fileName(const QString& filePath);
  QString SHARED_API fileNameWithoutExtension(const QString& filePath);
  QString SHARED_API fileNameExtension(const QString& filePath);
  QString SHARED_API unifySlahes(const QString& path);

  // TODO 
  QString SHARED_API exchangeFileName(const QString& filePath, const QString& before, const QString& after);

  // TODO
  //bool SHARED_API isDirectory(const QString& path);
  //bool SHARED_API isFile(const QString& path);

  QStringList SHARED_API split(const QString& path);
  QString SHARED_API join(const QStringList& splittedPath);


}

#endif