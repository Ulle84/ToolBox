#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>
#include <QApplication>

#include "IncludeFinder.h"

IncludeFinder::IncludeFinder()
{
  m_extensions << ".cpp";
  m_extensions << ".hpp";
  m_extensions << ".h";
}

QStringList IncludeFinder::files(const QStringList& directories, const QStringList& includes)
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

    m_commentHandler.removeComments(fileContent);

    QStringList lines = fileContent.split('\n');

    bool continueParsing = true;

    for (auto line = lines.begin(); line != lines.end() && continueParsing; ++line)
    {
      QString trimmed = line->trimmed();

      if (trimmed.startsWith("#include"))
      {
        for (auto include = includes.begin(); include != includes.end() && continueParsing; ++include)
        {
          if (trimmed.contains(*include))
          {
            result << *fileName;
            continueParsing = false;
          }
        }
      }
    }
  }

  return result;
}

void IncludeFinder::parsePotentialFiles(const QStringList& directories)
{
  m_potentialFiles.clear();

  for (auto it = directories.begin(); it != directories.end(); ++it)
  {
    QDirIterator dirIterator(*it, QDirIterator::Subdirectories);

    while (dirIterator.hasNext())
    {
      QString fileName = dirIterator.next();

      for (auto it2 = m_extensions.begin(); it2 != m_extensions.end(); ++it2)
      {
        if (fileName.endsWith(*it2))
        {
          m_potentialFiles << fileName;
          break;
        }
      }
    }
  }
}
