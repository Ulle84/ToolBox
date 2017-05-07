// created on 2017-03-03 by Ulrich Belitz

#ifndef PATH_H
#define PATH_H

#include <QString>
#include <QStringList>

namespace Path
{
  // TODO rename to applicationDirectory and configurationDirectory
  QString application();
  QString configuration();
  QString content();
  QString configurationFile(const QString& programName, const QString& fileName);
  QString testFile(const QString& moduleName, const QString& category, const QString& testName, const QString& fileName);
  QString portableProgram(const QString& programName);

  QString directory(const QString& filePath);
  QString fileName(const QString& filePath);
  QString fileNameWithoutExtension(const QString& filePath);
  QString fileNameExtension(const QString& filePath);
  QString unifySlahes(const QString& path);

  // TODO
  QString exchangeFileName(const QString& filePath, const QString& before, const QString& after);

  // TODO
  //bool isDirectory(const QString& path);
  //bool isFile(const QString& path);

  QStringList split(const QString& path);
  QString join(const QStringList& splittedPath);
}

#endif