#include <string>

#include <QFile>
#include <QTextStream>

#include <QMetaObject>
#include <QMetaMethod>

#include "ui_GeneratorQtWidgetsApplication.h"

#include "Class.h"
#include "GeneratorQtWidgetsApplication.h"
#include "XmlHelper.h"

GeneratorQtWidgetsApplication::GeneratorQtWidgetsApplication(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::GeneratorQtWidgetsApplication)
{
  ui->setupUi(this);

  connect(ui->lineEditName, &QLineEdit::textEdited, this, &GeneratorQtWidgetsApplication::optionsChanged);
}

GeneratorQtWidgetsApplication::~GeneratorQtWidgetsApplication()
{
  delete ui;
}

void GeneratorQtWidgetsApplication::readXml(QXmlStreamReader& xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    else if (xml.name() == "CreateBuildDir")
    {
      XmlHelper::readXml(xml, ui->checkBoxCreateBuildDir);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorQtWidgetsApplication::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  XmlHelper::writeXml(xml, "CreateBuildDir", ui->checkBoxCreateBuildDir);
}

QList<QPair<QString, QString>> GeneratorQtWidgetsApplication::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString newName = ui->lineEditName->text();

  QStringList textFiles;
  textFiles.append(":/files/Templates/QtWidgetsApplication/CMakeLists.txt");
  textFiles.append(":/files/Templates/QtWidgetsApplication/main.cpp");
  textFiles.append(":/files/Templates/QtWidgetsApplication/MainWindow.cpp");
  textFiles.append(":/files/Templates/QtWidgetsApplication/MainWindow.h");
  textFiles.append(":/files/Templates/QtWidgetsApplication/MainWindow.ui");
  textFiles.append(":/files/Templates/QtWidgetsApplication/QtWidgetsApplication.cpp");
  textFiles.append(":/files/Templates/QtWidgetsApplication/QtWidgetsApplication.h");
  textFiles.append(":/files/Templates/QtWidgetsApplication/QtWidgetsApplication.ui");

  for (auto it = textFiles.begin(); it != textFiles.end(); it++)
  {
    QFile file(*it);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
      return code;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    fileContent.replace(m_oldName, newName);

    QStringList splitted = it->split("/");

    for (int i = 0; i < m_fileOffset; ++i)
    {
      splitted.removeFirst();
    }

    QString fileName = splitted.join("/");
    fileName.replace(m_oldName, newName);

    code.append(qMakePair(fileName, fileContent));
  }

  return code;
}

QString GeneratorQtWidgetsApplication::integrationInstructions()
{
  return QString();
}

QList<QPair<QString, QString>> GeneratorQtWidgetsApplication::additionalResources()
{
  QList<QPair<QString, QString>> list;

  QString newName = ui->lineEditName->text();

  QStringList fileNameList;
  fileNameList.append(":/files/Templates/QtWidgetsApplication/Resources/logo.ico");
  fileNameList.append(":/files/Templates/QtWidgetsApplication/Resources/Resources.rc");
  fileNameList.append(":/files/Templates/QtWidgetsApplication/Resources/Resources.qrc");

  for (auto it = fileNameList.begin(); it != fileNameList.end(); it++)
  {
    QStringList splitted = it->split("/");

    for (int i = 0; i < m_fileOffset; ++i)
    {
      splitted.removeFirst();
    }

    QString newFileName = splitted.join("/");
    newFileName.replace(m_oldName, newName);

    list.append(qMakePair(newFileName, *it));
  }

  return list;
}

QString GeneratorQtWidgetsApplication::directory()
{
  if (ui->checkBoxCreateBuildDir->isChecked())
  {
    return ui->lineEditName->text();
  }
  else
  {
    return QString();
  }
}

