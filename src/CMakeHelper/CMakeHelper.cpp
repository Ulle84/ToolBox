#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QDebug>

#include "CMakeHelper.h"

CMakeHelper::CMakeHelper()
{
}

QStringList CMakeHelper::files(const QStringList& directories, const QString& searchString)
{
  parsePotentialFiles(directories);

  QStringList result;

  int counter = 1;

  for (auto fileName = m_potentialFiles.begin(); fileName != m_potentialFiles.end(); ++fileName, ++counter)
  {
    int percentage = 100.0 * counter / m_potentialFiles.length();

    emit notifyProgress(QString("parsing file %1 of %2 (%3% done)").arg(counter).arg(m_potentialFiles.length()).arg(percentage));
    QApplication::processEvents();

    QFile file(*fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
      continue;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    if (fileContent.toLower().contains(searchString.toLower()))
    {
      result << *fileName;
    }
  }

  return result;
}

void CMakeHelper::parsePotentialFiles(const QStringList& directories)
{
  m_potentialFiles.clear();

  for (auto it = directories.begin(); it != directories.end(); ++it)
  {
    QDirIterator dirIterator(*it, QDirIterator::Subdirectories);

    while (dirIterator.hasNext())
    {
      QString fileName = dirIterator.next();

      if (fileName.endsWith("CMakeLists.txt"))
      {
        m_potentialFiles << fileName;
      }
    }
  }
}
