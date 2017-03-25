// created on 2016-10-28

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <QString>

#include "SharedAPI.h"
#include "CustomTypes.h"

namespace Directory
{
  // save
	QString SHARED_API name(const QString& directoryPath);
	bool SHARED_API copy(const QString& source, const QString& destination);
	bool SHARED_API exists(const QString& directoryPath);
	QString SHARED_API moveUp(const QString& directoryPath, uint nLevels = 1);
	QString SHARED_API moveDown(const QString& directoryPath, const QString& directoryName);
	QString SHARED_API moveDown(const QString& directoryPath, const QStringList& directoryNames);
	

};

#endif