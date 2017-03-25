#include <QString>
#include <QStringList>
#include <QDir>
#include <QFileInfo>

#include "Directory.h"
#include "Path.h"

namespace Directory
{
  

	QString name(const QString& directoryPath)
	{
		QStringList splitted = Path::split(directoryPath);

		if (splitted.isEmpty())
			return QString();

		return splitted.last();
	}

	
		bool copy(const QString& source, const QString& destination)
		{
			QFileInfo srcFileInfo(source);

			if (srcFileInfo.isDir())
			{
				QDir targetDir(destination);
				targetDir.cdUp();
				if (!targetDir.mkdir(QFileInfo(destination).fileName()))
				{
					return false;
				}
				QDir sourceDir(source);
				QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
				foreach(const QString &fileName, fileNames)
				{
					const QString newSrcFilePath = source + QLatin1Char('/') + fileName;
					const QString newTgtFilePath = destination + QLatin1Char('/') + fileName;
					if (!copy(newSrcFilePath, newTgtFilePath))
						return false;
				}
			}
			else
			{
				if (!QFile::copy(source, destination))
					return false;
			}
			return true;
		
	}

		bool exists(const QString& directoryPath)
		{
			QFileInfo srcFileInfo(directoryPath);
			return srcFileInfo.isDir();
		}

		QString SHARED_API moveUp(const QString& directoryPath, uint nLevels)
		{
			QStringList splitted = Path::split(directoryPath);
			if (splitted.length() < nLevels)
				return QString();

			for (int i = 0; i < nLevels; ++i)
				splitted.removeLast();

			return Path::join(splitted);
		}

		QString moveDown(const QString& directoryPath, const QString& directoryName)
		{
			return Path::unifySlahes(directoryPath) + '/' + directoryName;
		}

		QString moveDown(const QString& directoryPath, const QStringList& directoryNames)
		{
			QString directory = Path::unifySlahes(directoryPath);

			for (auto it : directoryNames)
			{
				directory.append('/');
				directory.append(it);
			}

			return directory;
		}

}