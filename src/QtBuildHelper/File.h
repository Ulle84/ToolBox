// created on 2016-10-28

#ifndef FILE_H
#define FILE_H

#include <QMap>
#include <QString>
#include <QStringList>

namespace File
{
  // save
  bool stringMapToFile(const QMap<QString, QString>& map, const QString& filePath);
  bool stringToFile(const QString& fileContent, const QString& filePath);
  bool stringListToFile(const QStringList& fileContent, const QString& filePath);

  // load
  QString fileToString(const QString& filePath);
  QStringList fileToStringList(const QString& filePath);
  QMap<QString, QString> fileToStringMap(const QString& filePath);

  // misc
  QString directory(const QString& filePath);
  QString checkSum(const QString& filePath);
  QStringList merge(const QStringList& filePaths);
  QString name(const QString& filePath);
};

#endif