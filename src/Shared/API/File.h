// created on 2016-10-28

#ifndef FILE_H
#define FILE_H

#include <QMap>
#include <QString>
#include <QStringList>

#include "SharedAPI.h"

// TODO move some functions to Converter

namespace File
{
  // save
  bool SHARED_API stringMapToFile(const QMap<QString, QString>& map, const QString& filePath);
  bool SHARED_API stringToFile(const QString& fileContent, const QString& filePath);
  bool SHARED_API stringListToFile(const QStringList& fileContent, const QString& filePath);

  // load
  QString SHARED_API fileToString(const QString& filePath);
  QStringList SHARED_API fileToStringList(const QString& filePath);
  QMap<QString, QString> SHARED_API fileToStringMap(const QString& filePath);

  // misc
  QString SHARED_API directory(const QString& filePath);
  QString SHARED_API checkSum(const QString& filePath);
  QStringList SHARED_API merge(const QStringList& filePaths);
  QString SHARED_API name(const QString& filePath);
};

#endif