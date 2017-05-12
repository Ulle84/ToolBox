#include <iostream>

#include <QDebug>
#include <QDateTime>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QMap>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QCoreApplication>

#include "CommentHandler.h"
#include "File.h"
#include "IntHelper.h"
#include "CppHelper.h"

#include "BlockCodeFormatter.h"
#include "CodeCleaner.h"
#include "ConsoleHelper.h"
#include "Options.h"
#include "Console.h"
#include "CppHelper.h"
#include "Path.h"

#include "windows.h"

int main(int argc, char* argv[])
{
  QCoreApplication coreApplication(argc, argv);

  // sleep for one second, so timestamps are definitely different
  Sleep(1000); // TODO make configurable via command line argument

  bool codeCleanerEnabled = true;
  // TODO if argc is wrong -> show info about parameters

  // TODO do sanity check on code - if code is not compilable return immediately

  //Console::showInfo("CodeCleaner");
  //return 0;

  // "-csf" || "--checkSumFile"
  // "-cf" || "--configFile"
  // "-isd" || "--includeSubDirectories"
  // "-f" || "--files"
  // "-xf" || "--excludedFiles"
  // "-d" || "--directories"
  // "-xd" || "--excludedDirectories"

  Options options;
  options.parseCommandLineArguments(argc, argv);
  options.print();

  QString aStylePath = Path::application() + "/AStyle.exe";

  QFile aStyle(aStylePath);
  bool aStyleExists = aStyle.exists();

  if (!aStyleExists)
  {
    std::cout << "CodeCleaner: WARNING - AStyle not found!" << std::endl;
  }

  for (auto it = options.m_directories.begin(); it != options.m_directories.end(); ++it)
  {
    QDirIterator dirIt(*it, options.m_includeSubdirectories ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags);

    while (dirIt.hasNext())
    {
      QString fileName = dirIt.next();

      if (options.extensionAllowed(fileName))
      {
        options.m_files.append(fileName);
      }
    }
  }

  QStringMap checkSums;

  if (!options.m_checkSumsFileName.isEmpty())
  {
    checkSums = File(options.m_checkSumsFileName).toStringMap();
  }

  QList<int> filesToRemove;

  int counter = 0;

  for (auto it = options.m_files.begin(); it != options.m_files.end(); ++it)
  {
    bool removed = false;

    for (auto it2 = options.m_excludedFiles.begin(); it2 != options.m_excludedFiles.end(); ++it2)
    {
      if (it->endsWith(*it2))
      {
        filesToRemove.prepend(counter);
        removed = true;
      }
    }

    if (!removed)
    {
      for (auto it2 = options.m_excludedDirectories.begin(); it2 != options.m_excludedDirectories.end(); ++it2)
      {
        if (it->contains(*it2))
        {
          filesToRemove.prepend(counter);
        }
      }
    }

    if (!removed)
    {
      if (checkSums.contains(*it))
      {
        if (checkSums[*it] == File(*it).checkSum())
        {
          // file did not change since last run - so we can skip it!
          filesToRemove.prepend(counter);
        }
      }
    }

    counter++;
  }

  for (auto it = filesToRemove.begin(); it != filesToRemove.end(); ++it)
  {
    options.m_files.removeAt(*it);
  }

  CodeCleaner codeCleaner;
  codeCleaner.setOptions(options);

  CppHelper cppHelper;

  int numberOfFiles = options.m_files.length();

  int fileCounter = 0;

  for (auto it = options.m_files.begin(); it != options.m_files.end(); ++it)
  {
    fileCounter++;
    QString fileName(*it);

    std::cout << QString("CodeCleaner: processing file %1%2 of %3: %4").arg(QString::fromStdString(IntHelper::fillString(fileCounter, numberOfFiles, '0'))).arg(fileCounter).arg(numberOfFiles).arg(fileName).toStdString() << std::endl;

    if (!options.extensionAllowed(fileName))
    {
      std::cout << "CodeCleaner: file has unallowed extension" << std::endl;
      continue;
    }

    QFile fileIn(fileName);

    if (!fileIn.exists())
    {
      std::cout << "CodeCleaner: file does not exist" << std::endl;
      continue;
    }

    QStringList aStyleArguments;
    CodeCleaner::CodeType codeType = CodeCleaner::CodeType::Undefined;

    if (fileName.endsWith(".cpp"))
    {
      codeType = CodeCleaner::CodeType::Implementation;
      aStyleArguments << "--options=" + Path::configurationFile("CodeCleaner", "AStyleOptionsCpp.txt");
    }
    else if (fileName.endsWith(".h") || fileName.endsWith(".hpp"))
    {
      codeType = CodeCleaner::CodeType::Declaration;
      aStyleArguments << "--options=" + Path::configurationFile("CodeCleaner", "AStyleOptionsH.txt");
    }

    if (aStyleExists && options.m_runAStyle)
    {
      aStyleArguments << fileName;
      QProcess process;
      process.closeReadChannel(QProcess::StandardOutput);
      process.closeReadChannel(QProcess::StandardError);
      process.start(aStylePath, aStyleArguments);
      process.waitForFinished(-1);
    }

    if (codeCleanerEnabled)
    {
      if (!fileIn.open(QFile::ReadOnly | QFile::Text))
      {
        std::cout << "CodeCleaner: can not open file for reading" << std::endl;
        continue;
      }

      QTextStream textStreamIn(&fileIn);

      QString code = textStreamIn.readAll();
      fileIn.close();

      QString original = code;

      //codeCleaner.process(code, codeType);
      cppHelper.clean(code);

      if (code != original)
      {
        QFile fileOut(fileName);

        if (!fileOut.open(QFile::WriteOnly | QFile::Text))
        {
          std::cout << "CodeCleaner: can not open file for writing" << std::endl;
          continue;
        }

        QTextStream textStreamOut(&fileOut);
        textStreamOut << code;
        fileOut.close();
      }
    }

  }

  /*if (fileCounter == 0)
  {
    std::cout << std::endl << "CodeCleaner: nothing to do!" << std::endl;
  }
  else
  {
    std::cout << std::endl << "CodeCleaner: finished!" << std::endl;
  }*/

  if (!options.m_checkSumsFileName.isEmpty())
  {
    for (auto it = options.m_files.begin(); it != options.m_files.end(); ++it)
    {
      checkSums[*it] = File(*it).checkSum();
    }

    File(options.m_checkSumsFileName).write(checkSums);
  }

  return 0;
}
