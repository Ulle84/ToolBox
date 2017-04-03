// created on 2017-03-03 by Ulrich Belitz

//#include <QDir>
#include <QStringList>
#include <QCoreApplication>

#include "Path.h"

namespace Path
{

  QString Path::testFile(const QString& moduleName, const QString& category, const QString& testName, const QString& fileName)
  {
    QStringList stringList;
    stringList << QCoreApplication::applicationDirPath();
    stringList << ".." << "src" << "TestFiles" << moduleName << category << testName << fileName;

    return stringList.join('/');
  }

  QString SHARED_API application()
  {
    return QCoreApplication::applicationDirPath();
  }

  QString SHARED_API configuration()
  {
    QStringList stringList;
    stringList << QCoreApplication::applicationDirPath();
    stringList << ".." << "configuration";

    return stringList.join('/');
  }

  QString SHARED_API configurationFile(const QString& programName, const QString& fileName)
  {
    QStringList stringList;
    stringList << configuration() << programName << fileName;

    return stringList.join('/');
  }

  QString SHARED_API portableProgram(const QString& programName)
  {
    QString program = Path::application();
    program.append(QString("/../../PortablePrograms/%1/%1.exe").arg(programName));
    return program;
  }

  QString directory(const QString& filePath)
  {
	  QStringList splitted = split(filePath);

	  if (splitted.isEmpty())
		  return QString();


	  splitted.removeLast();

	  return join(splitted);
	
  }

  QString fileName(const QString& filePath)
  {
	  QStringList splitted = split(filePath);

	  if (splitted.isEmpty())
		  return QString();

	  return splitted.last();
  }

  QString fileNameWithoutExtension(const QString& filePath)
  {
	  QString fileName = Path::fileName(filePath);

	  int index = fileName.lastIndexOf('.');

	  if (index < 0)
		  return QString();

	  return fileName.left(index);


	  
  }

  QString fileNameExtension(const QString& filePath)
  {
	  QString fileName = Path::fileName(filePath);

	  int index = fileName.lastIndexOf('.');

	  if (index < 0)
		  return QString();

	  return fileName.mid(index + 1);
  }

  QString unifySlahes(const QString& path)
  {
	  QString string = path;
	  string.replace('\\', '/');
	  return string;
  }


  QString SHARED_API exchangeFileName(const QString& filePath, const QString& before, const QString& after)
  {
	  int startIndex = filePath.lastIndexOf('/');
	  int endIndex = filePath.lastIndexOf('.');

	  if (startIndex < 0 || endIndex < 0 || endIndex < startIndex)
		  return QString();

	  ++startIndex;

	  int length = endIndex - startIndex;

	  QString fileName = filePath.mid(startIndex, length);
	  fileName.replace(before, after);

	  QString changedFilePath(filePath);
	  changedFilePath.replace(startIndex, length, fileName);

	  return changedFilePath;
  }

  /*bool isDirectory(const QString& path)
  {
	  return false; // TODO
  }

  bool isFile(const QString& path)
  {
	  return false; // TODO
  }*/

  QStringList SHARED_API split(const QString& path)
  {
	  return unifySlahes(path).split('/', QString::SkipEmptyParts);
  }

  QString SHARED_API join(const QStringList& splittedPath)
  {
	  return splittedPath.join('/');
  }

}
