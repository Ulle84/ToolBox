// created on 2017-01-24 by Ulrich Belitz

//#include <iostream>

// TODO check if all includes are really required
#include <QFile>
#include <QFileInfo>
#include <QDirIterator>
#include <QProcess>
#include <QList>
#include <QStringList>

#include "Arguments.h"
#include "Helper.h"
#include "Tool.h"

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
  QMap<QString, QString> timeStampsSrc = Helper::fileToStringMap(timeStampSrcPath);

  QList<Tool> tools;  
  tools.append(Tool("repc", ".rep", ".h", "rep_"));
  tools.append(Tool("rcc", ".qrc", ".cpp", "qrc_"));
  tools.append(Tool("moc", ".h", ".cpp", "moc_"));
  tools.append(Tool("uic", ".ui", ".h", "ui_"));  

  Helper::removeExcludedTools(tools, excludedTools);

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
        int startPosition = input.lastIndexOf('/') + 1; // TODO what about \ seperator?
        QString className = input.mid(startPosition, input.lastIndexOf('.') - startPosition);

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
        QString lastModfied = Helper::toString(fileInfo.lastModified());

        if (timeStampsSrc[input] != lastModfied)
        {
          timeStampsSrc[input] = lastModfied;

          if (it.m_toolName == "moc")
          {
            if (!Helper::fileToString(input).contains("Q_OBJECT"))
            {
              continue;
            }
          }

          QString output =  Helper::fileName(input).replace(it.m_inputFileExtension, it.m_outputFileExtension).prepend(it.m_outputFilePrefix);

          output.prepend(QDir::separator());

          if (it.m_toolName == "repc")
          {
            output.prepend("API");
            output.prepend(QDir::separator());
            output.prepend(inputDirectory);
          }
          else
          {
            output.prepend(outputDirectory);
          }

          

          Helper::showMessage(QString("QtBuildHelper: %1'ing %2").arg(it.m_toolName).arg(input).toStdString());

          // repc.exe -i rep -o merged D:\ube\Qt\directconnectserver\simpleswitch.rep D:\ube\Qt\directconnectserver\repcTest.h

          QStringList parameters;

          if (it.m_toolName == "repc")
          {
            parameters << "-i" << "rep" << "-o" << "merged" << input << output;
          }
          else
          {
            parameters << "-o" << output;

            if (it.m_toolName == "moc")
            {
              parameters << "-I" << qtIncludeDirectory;
            }

            parameters << input;
          }

          

          int result = QProcess::execute(toolPath, parameters);

          if (it.m_toolName == "repc" && result == 0)
          {
            QString fileContent = Helper::fileToString(output);

            QString searchFor = QString("class %1").arg(className);
            QString repleaceBy = QString("class %1 %2").arg(QString("%1_API").arg(className.toUpper())).arg(className);

            fileContent.replace(searchFor, repleaceBy);

            Helper::stringToFile(fileContent, output);
            

            

          }
        }
      }
    }
    else
    {
      Helper::showError(it.m_toolName.toStdString() + ".exe not found");
    }
  }

  Helper::stringMapToFile(timeStampsSrc, timeStampSrcPath);

  
  QString timeStampGeneratedPath = outputDirectory + "/QtBuildHelperGenerated.txt";
  QMap<QString, QString> timeStampsGenerated = Helper::fileToStringMap(timeStampGeneratedPath);

  QDirIterator dirIterator(outputDirectory, QStringList() << "*.cpp");
  QStringList generatedFiles;
  bool rewriteNecessary = false;

  while (dirIterator.hasNext())
  {
    QString generatedFile = dirIterator.next();

    if (!(Helper::fileName(generatedFile).startsWith("moc_") || Helper::fileName(generatedFile).startsWith("qrc_")))
    {
      continue;
    }

    generatedFiles.prepend(generatedFile);

    QFileInfo fileInfo(generatedFile);
    QString lastModfied = Helper::toString(fileInfo.lastModified());

    if (timeStampsGenerated[generatedFile] != lastModfied)
    {
      timeStampsGenerated[generatedFile] = lastModfied;
      rewriteNecessary = true;
    }
  }

  if (rewriteNecessary)
  {
    QString fileNameOfGeneratedFile = "QtBuildHelperOutput.cpp";

    Helper::showMessage(QString("QtBuildHelper: updating file %1").arg(fileNameOfGeneratedFile).toStdString());

    QStringList fileContent;
    fileContent.append("/* file is generated by QtBuildHelper - changes will be overwritten */");

    for (auto& it : generatedFiles)
    {
      fileContent.append(QString("#include \"%1\"").arg(Helper::fileName(it)));
    }

    Helper::stringListToFile(fileContent, outputDirectory + "/" + fileNameOfGeneratedFile);
    Helper::stringMapToFile(timeStampsGenerated, timeStampGeneratedPath);
  }

  return 0;
}
