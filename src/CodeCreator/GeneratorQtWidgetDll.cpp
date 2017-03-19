// created on 2017-01-23 by Ulrich Belitz

#include <QFile>
#include <QTextStream>

#include "ui_GeneratorQtWidgetDll.h"

#include "Class.h"
#include "GeneratorQtWidgetDll.h"
#include "XmlHelper.h"
#include "QStringEx.h"

GeneratorQtWidgetDll::GeneratorQtWidgetDll(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::GeneratorQtWidgetDll)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
}

GeneratorQtWidgetDll::~GeneratorQtWidgetDll()
{
  delete ui;
}

void GeneratorQtWidgetDll::readXml(QXmlStreamReader& xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorQtWidgetDll::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
}

QList<QPair<QString, QString>> GeneratorQtWidgetDll::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString newName = ui->lineEditName->text();

  QStringList files;
  files.append(":/files/Templates/QtWidgetDll/API/QtWidgetDll.h");
  files.append(":/files/Templates/QtWidgetDll/API/QtWidgetDllAPI.h");
  files.append(":/files/Templates/QtWidgetDll/CMakeLists.txt");
  files.append(":/files/Templates/QtWidgetDll/QtWidgetDll.cpp");
  files.append(":/files/Templates/QtWidgetDll/QtWidgetDll.ui");
  files.append(":/files/Templates/QtWidgetDll/QtWidgetDllDesignerPlugin.cpp");
  files.append(":/files/Templates/QtWidgetDll/QtWidgetDllDesignerPlugin.h");
  files.append(":/files/Templates/QtWidgetDll/QtWidgetDllDesignerPlugin.json");


  for (auto it = files.begin(); it != files.end(); it++)
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
    fileContent.replace(m_oldName.toUpper(), newName.toUpper());
    fileContent.replace(QStringEx::lowercaseFirstLetter(m_oldName), QStringEx::lowercaseFirstLetter(newName));

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

QString GeneratorQtWidgetDll::integrationInstructions()
{
  return QString();
}

QList<QPair<QString, QString>> GeneratorQtWidgetDll::additionalResources()
{
  QList<QPair<QString, QString>> list;

  QString newName = ui->lineEditName->text();

  QStringList fileNameList;
  fileNameList.append(":/files/Templates/QtWidgetDll/QtWidgetDll.rc");

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

QString GeneratorQtWidgetDll::directory()
{
  return QString();
}