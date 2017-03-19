// created on 2017-01-24 by Ulrich Belitz

#include <iostream>

#include <QFile>
#include <QFileInfo>
#include <QDirIterator>
#include <QProcess>
#include <QList>
#include <QStringList>

#include "Arguments.h"
#include "Console.h"
#include "File.h"
#include "QDateTimeEx.h"
#include "Tool.h"

QString fileName(const QString& filePath)
{
  QStringList stringList = filePath.split("/");

  return stringList.isEmpty() ? QString() : stringList.last();  
}

void removeExcludedTools(QList<Tool>& tools, const QStringList& excludedTools)
{
  if (!excludedTools.isEmpty())
  {
    for (auto& excludedTool : excludedTools)
    {
      for (int i = 0; i < tools.length(); ++i)
      {
        if (tools[i].m_toolName.toLower() == excludedTool.toLower())
        {
          tools.removeAt(i);
          break;
        }
      }
    }    
  }
}

int main(int argc, char* argv[])
{
  Arguments arguments(argc, argv);

  QString inputDirectory = arguments.argument("-id");  
  QString outputDirectory = arguments.argument("-od");
  QString qtBinDirectory = arguments.argument("-qbd");
  QString qtIncludeDirectory = arguments.argument("-qid");
  QStringList excludedDirectories = arguments.arguments("-ed");
  QStringList excludedTools = arguments.arguments("-et");

  QString timeStampSrcPath = outputDirectory + "/QtBuildHelperSrc.txt";
  QMap<QString, QString> timeStampsSrc = File::fileToStringMap(timeStampSrcPath);

  QList<Tool> tools;  
  tools.append(Tool("rcc", ".qrc", ".cpp", "qrc_"));
  tools.append(Tool("moc", ".h", ".cpp", "moc_"));
  tools.append(Tool("uic", ".ui", ".h", "ui_"));

  removeExcludedTools(tools, excludedTools);

  // TODO rcc: parse qrc file, and check, if a file inside the resource file has changed -> if yes - recompile  

  for (auto it : tools)
  {
    QString toolPath = qtBinDirectory + "/" + it.m_toolName + ".exe";
    QFile tool(toolPath);

    if (tool.exists())
    {
      QDirIterator dirIterator(inputDirectory, QStringList() << "*" + it.m_inputFileExtension, QDir::NoFilter, QDirIterator::Subdirectories);

      while (dirIterator.hasNext())
      {
        QString input = dirIterator.next();

        bool processFile = true;
        for (auto it : excludedDirectories)
        {
          if (input.startsWith(it))
          {
            processFile = false;
            break;
          }
        }

        if (!processFile)
        {
          continue;
        }

        QFileInfo fileInfo(input);
        QString lastModfied = QDateTimeEx::toString(fileInfo.lastModified());

        if (timeStampsSrc[input] != lastModfied)
        {
          timeStampsSrc[input] = lastModfied;

          if (it.m_toolName == "moc")
          {
            if (!File::fileToString(input).contains("Q_OBJECT"))
            {
              continue;
            }
          }

          QString output =  fileName(input).replace(it.m_inputFileExtension, it.m_outputFileExtension).prepend(it.m_outputFilePrefix);

          output.prepend(QDir::separator());
          output.prepend(outputDirectory);

          Console::showMessage(QString("QtBuildHelper: %1'ing %2").arg(it.m_toolName).arg(input).toStdString());

          QStringList parameters;
          parameters << "-o" << output;

          if (it.m_toolName == "moc")
          {
            parameters << "-I" << qtIncludeDirectory;
          }

          parameters << input;

          QProcess::execute(toolPath, parameters);          
        }
      }
    }
    else
    {
      Console::showError(it.m_toolName.toStdString() + ".exe not found");
    }
  }

  File::stringMapToFile(timeStampsSrc, timeStampSrcPath);

  
  QString timeStampGeneratedPath = outputDirectory + "/QtBuildHelperGenerated.txt";
  QMap<QString, QString> timeStampsGenerated = File::fileToStringMap(timeStampGeneratedPath);

  QDirIterator dirIterator(outputDirectory, QStringList() << "*.cpp");
  QStringList generatedFiles;
  bool rewriteNecessary = false;

  while (dirIterator.hasNext())
  {
    QString generatedFile = dirIterator.next();

    if (!(fileName(generatedFile).startsWith("moc_") || fileName(generatedFile).startsWith("qrc_")))
    {
      continue;
    }

    generatedFiles.prepend(generatedFile);

    QFileInfo fileInfo(generatedFile);
    QString lastModfied = QDateTimeEx::toString(fileInfo.lastModified());

    if (timeStampsGenerated[generatedFile] != lastModfied)
    {
      timeStampsGenerated[generatedFile] = lastModfied;
      rewriteNecessary = true;
    }
  }

  if (rewriteNecessary)
  {
    QString fileNameOfGeneratedFile = "generated.cpp";

    Console::showMessage(QString("QtBuildHelper: updating file %1").arg(fileNameOfGeneratedFile).toStdString());

    QStringList fileContent;
    fileContent.append("/* file is generated automatically - changes will be overwritten */");

    for (auto& it : generatedFiles)
    {
      fileContent.append(QString("#include \"%1\"").arg(fileName(it)));
    }

    File::stringListToFile(fileContent, outputDirectory + "/" + fileNameOfGeneratedFile);
    File::stringMapToFile(timeStampsGenerated, timeStampGeneratedPath);
  }

  return 0;
}
