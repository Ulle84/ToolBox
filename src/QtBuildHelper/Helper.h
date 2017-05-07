#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QList>
#include <QMap>

#include "Tool.h"

namespace Helper
{
  QString fileName(const QString& filePath);
  void removeExcludedTools(QList<Tool>& tools, const QStringList& excludedTools);

  void showMessage(const std::string& message);
  void showError(const std::string& error);

  QMap<QString, QString> fileToStringMap(const QString& filePath);
  QStringList fileToStringList(const QString& filePath);
  QString fileToString(const QString& filePath);

  bool stringMapToFile(const QMap<QString, QString>& map, const QString& filePath);
  bool stringToFile(const QString& fileContent, const QString& filePath);
  bool stringListToFile(const QStringList& fileContent, const QString& filePath);

  QString toString(const QDateTime& dateTime);
}

#endif