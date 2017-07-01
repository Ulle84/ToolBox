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
#include "Compiler.h"

int main(int argc, char* argv[])
{
  Arguments arguments(argc, argv);

  QString inputDirectory = arguments.argument("-id");
  QString outputDirectory = arguments.argument("-od");
  QString qtBinDirectory = arguments.argument("-qbd");
  QString qtIncludeDirectory = arguments.argument("-qid");
  QStringList excludedDirectories = arguments.arguments("-ed");
  QString apiDefine = arguments.argument("-ad");

  QString timeStampSrcPath = outputDirectory + "/QtBuildHelperSrc.txt";
  QMap<QString, QString> timeStampsSrc = Helper::fileToStringMap(timeStampSrcPath);

  QList<Compiler> compilers;


  
  Compiler replica = Compiler(Compiler::Type::Replica, "repc", ".rep", ".h", "Replica");
  Compiler source = Compiler(Compiler::Type::Source, "repc", ".rep", ".h", "Source");
  Compiler rcc = Compiler(Compiler::Type::Resources, "rcc", ".qrc", ".cpp", "Qrc");
  Compiler moc = Compiler(Compiler::Type::MetaObject, "moc", ".h", ".cpp", "Moc");
  Compiler uic = Compiler(Compiler::Type::UserInterface, "uic", ".ui", ".h", "Ui");

  // do not change order!
  compilers.append(source);
  compilers.append(replica);  
  compilers.append(rcc);
  compilers.append(moc);
  compilers.append(uic);

  // TODO rcc: parse qrc file, and check, if a file inside the resource file has changed -> if yes - recompile

  for (auto it : compilers)
  {
    QString compilerPath = qtBinDirectory + "/" + it.m_name + ".exe";
    QFile compiler(compilerPath);

    if (compiler.exists())
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
        QString lastModfied = Helper::toString(fileInfo.lastModified());

        if (timeStampsSrc[input] != lastModfied)
        {
          if (it.m_type != Compiler::Type::Source)
            timeStampsSrc[input] = lastModfied;

          if (it.m_type == Compiler::Type::MetaObject)
          {
            if (!Helper::fileToString(input).contains("Q_OBJECT"))
            {
              continue;
            }
          }

          

          QString output = Helper::fileName(input).replace(it.m_inputFileExtension, it.m_outputFileExtension);

         
            output.insert(output.lastIndexOf('.'), it.m_outputFileSuffix);
          

          



          output.prepend(QDir::separator());

          if (it.m_type == Compiler::Type::Replica || it.m_type == Compiler::Type::Source)
          {
            output.prepend("API");
            output.prepend(QDir::separator());
            output.prepend(inputDirectory);
          }
          else
          {
            output.prepend(outputDirectory);
          }

          Helper::showMessage(QString("QtBuildHelper: %1'ing %2").arg(it.m_name).arg(input).toStdString());

          

          QStringList parameters;

          if (it.m_type == Compiler::Type::Replica)
          {
            parameters << "-i" << "rep" << "-o" << "replica" << input << output;
          }
          else if (it.m_type == Compiler::Type::Source)
          {
            parameters << "-i" << "rep" << "-o" << "source" << input << output;
          }
          else
          {
            parameters << "-o" << output;

            if (it.m_type == Compiler::Type::MetaObject)
            {
              parameters << "-I" << qtIncludeDirectory;
            }

            parameters << input;
          }

          int result = QProcess::execute(compilerPath, parameters);

          if (result == 0)
          {
            QString fileContent = Helper::fileToString(output);

            if (it.m_type == Compiler::Type::Replica || it.m_type == Compiler::Type::Source)
            {
              

              fileContent.replace("\nclass ", QString("\nclass %1 ").arg(apiDefine));

              
            }
            else if (it.m_type == Compiler::Type::UserInterface)
            {
              int positionClass = fileContent.indexOf("class Ui_");

              if (positionClass != -1)
              {
                fileContent.remove(positionClass + 6, 3);

                int positionNewLine = fileContent.indexOf('\n', positionClass);

                if (positionNewLine != -1)
                {
                  fileContent.insert(positionNewLine, "Ui");
                }
              }

              QString endTag = "// namespace Ui";

              int positionNamespaceStart = fileContent.indexOf("namespace Ui");
              int positionNamespaceEnd = fileContent.indexOf(endTag);         

              if (positionNamespaceStart != -1 && positionNamespaceEnd != -1)
                fileContent.remove(positionNamespaceStart, positionNamespaceEnd - positionNamespaceStart + endTag.length() + 2);

            }
            Helper::stringToFile(fileContent, output);
          }

          
        }
      }
    }
    else
    {
      Helper::showError(it.m_name.toStdString() + ".exe not found");
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

    if (Helper::fileName(generatedFile).endsWith(moc.m_outputFileSuffix + moc.m_outputFileExtension))
    {
      generatedFiles.append(generatedFile);
    }
    else if (Helper::fileName(generatedFile).endsWith(rcc.m_outputFileSuffix + rcc.m_outputFileExtension))
    {
      generatedFiles.prepend(generatedFile);
    }
    else
    {
      continue;
    }

    
    

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
