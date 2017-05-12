#include <QString>
#include <QDebug>

#include "Options.h"
#include "File.h"

Options::Options()
{
  m_allowedExtensions << ".cpp" << ".hpp" << ".h";
}

void Options::parseCommandLineArguments(int argc, char* argv[])
{
  m_arguments.clear();

  for (int i = 1; i < argc; i++)
  {
    QString argument = argv[i];

    if (argument == "-cf")
    {
      i++;

      if (i < argc)
      {
        QString fileName = argv[i];
        m_arguments.append(File(fileName).toStringList());
      }
    }

    else
    {
      m_arguments.append(argument);
    }
  }

  applyCommandLineArguments();

  convertSlashes();
}

void Options::applyCommandLineArguments()
{
  QStringList* toAppend = nullptr;

  for (auto it = m_arguments.begin(); it != m_arguments.end(); ++it)
  {
    QString argument = it->trimmed();

    if (argument.isEmpty() || argument.startsWith('#') || argument.startsWith("//"))
    {
      continue;
    }

    if (argument.startsWith('-'))
    {
      toAppend = nullptr;
    }
    else
    {
      if (toAppend != nullptr)
      {
        toAppend->append(argument);
      }
    }

    if (argument == "-b")
    {
      m_doBlockCodeFormatting = true;
    }
    else if (argument == "-r")
    {
      // rigorous mode
      enableAll();
    }
    else if (argument == "-m")
    {
      m_addMPrefixToMembers = true;
    }
    else if (argument == "-isd" || argument == "-includeSubdirectories")
    {
      m_includeSubdirectories = true;
    }
    else if (argument == "-csf" || argument == "--checkSumFile")
    {
      it++;

      if (it != m_arguments.end())
      {
        m_checkSumsFileName = it->trimmed();
      }
    }
    else if (argument == "-f")
    {
      toAppend = &m_files;
    }
    else if (argument == "-xf")
    {
      toAppend = &m_excludedFiles;
    }
    else if (argument == "-d")
    {
      toAppend = &m_directories;
    }
    else if (argument == "-xd")
    {
      toAppend = &m_excludedDirectories;
    }
  }
}

void Options::convertSlashes()
{
  for (auto it = m_files.begin(); it != m_files.end(); ++it)
  {
    it->replace("\\", "/");
  }

  for (auto it = m_directories.begin(); it != m_directories.end(); ++it)
  {
    it->replace("\\", "/");
  }

  for (auto it = m_excludedFiles.begin(); it != m_excludedFiles.end(); ++it)
  {
    it->replace("\\", "/");
  }

  for (auto it = m_excludedDirectories.begin(); it != m_excludedDirectories.end(); ++it)
  {
    it->replace("\\", "/");
  }
}

void Options::enableAll(bool enabled)
{
  //# = #
  m_beautify                             = enabled;
  m_cleanElementInitializiers            = enabled;
  m_doBlockCodeFormatting                = enabled;
  m_includeSubdirectories                = enabled;
  m_removeDoubleEmptyLines               = enabled;
  m_removeUnnecessarySpaces              = enabled;
  m_removeEmptyLinesAfterOpeningBracket  = enabled;
  m_removeEmptyLinesBeforeClosingBracket = enabled;
  m_removeUnnecessaryStuff               = enabled;
  m_runAStyle                            = enabled;
  //m_addMPrefixToMembers                = enabled;
}

void Options::print()
{
  qDebug() << "options:";

  //#" << # ? #
  qDebug() << "addMPrefixToMembers " << (m_addMPrefixToMembers                  ? "ON" : "OFF");
  qDebug() << "beautify " << (m_beautify                             ? "ON" : "OFF");
  qDebug() << "cleanElementInitializiers " << (m_cleanElementInitializiers            ? "ON" : "OFF");
  qDebug() << "doBlockCodeFormatting " << (m_doBlockCodeFormatting                ? "ON" : "OFF");
  qDebug() << "includeSubdirectories " << (m_includeSubdirectories                ? "ON" : "OFF");
  qDebug() << "removeDoubleEmptyLines " << (m_removeDoubleEmptyLines               ? "ON" : "OFF");
  qDebug() << "removeUnnecessarySpaces " << (m_removeUnnecessarySpaces              ? "ON" : "OFF");
  qDebug() << "removeEmptyLinesAfterOpeningBracket " << (m_removeEmptyLinesAfterOpeningBracket  ? "ON" : "OFF");
  qDebug() << "removeEmptyLinesBeforeClosingBracket " << (m_removeEmptyLinesBeforeClosingBracket ? "ON" : "OFF");
  qDebug() << "removeLineBreaksInsideParentheses " << (m_removeLineBreaksInsideParentheses    ? "ON" : "OFF");
  qDebug() << "removeUnnecessaryStuff " << (m_removeUnnecessaryStuff ? "ON" : "OFF");
  qDebug() << "cleanComments " << (m_cleanComments ? "ON" : "OFF");
  qDebug() << "runAStyle " << (m_runAStyle                            ? "ON" : "OFF");

  if (!m_checkSumsFileName.isEmpty())
  {
    qDebug() << "\ncheck sum file:" << m_checkSumsFileName;
  }

  if (!m_files.isEmpty())
  {
    qDebug() << "\nfiles:";

    for (auto it = m_files.begin(); it != m_files.end(); ++it)
    {
      qDebug() << *it;
    }
  }

  if (!m_directories.isEmpty())
  {
    qDebug() << "\ndirectories:";

    for (auto it = m_directories.begin(); it != m_directories.end(); ++it)
    {
      qDebug() << *it;
    }
  }

  if (!m_excludedFiles.isEmpty())
  {
    qDebug() << "\nexcluded files:";

    for (auto it = m_excludedFiles.begin(); it != m_excludedFiles.end(); ++it)
    {
      qDebug() << *it;
    }
  }

  if (!m_excludedDirectories.isEmpty())
  {
    qDebug() << "\nexcluded directories:";

    for (auto it = m_excludedDirectories.begin(); it != m_excludedDirectories.end(); ++it)
    {
      qDebug() << *it;
    }
  }
}

bool Options::extensionAllowed(const QString& fileName)
{
  for (auto it = m_allowedExtensions.begin(); it != m_allowedExtensions.end(); ++it)
  {
    if (fileName.endsWith(*it))
    {
      return true;
    }
  }

  return false;
}
