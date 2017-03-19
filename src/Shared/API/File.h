// created on 2016-10-28

#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QStringList>

#include "SharedAPI.h"

// TODO move some functions to Converter

namespace File
{
  // save
  bool SHARED_API stringMapToFile(const QMap<QString, QString>& map, const QString& fileName);
  bool SHARED_API stringToFile(const QString& fileContent, const QString& fileName);
  bool SHARED_API stringListToFile(const QStringList& fileContent, const QString& fileName);

  // load
  QString SHARED_API fileToString(const QString& fileName);
  QStringList SHARED_API fileToStringList(const QString& fileName);
  QMap<QString, QString> SHARED_API fileToStringMap(const QString& fileName);

  QString SHARED_API directory(const QString& fileName);
  QString SHARED_API checkSum(const QString& fileName);
};

#endif