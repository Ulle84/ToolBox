// created on 2017-01-23 by Ulrich Belitz

#include <QFile>
#include <QTextStream>

#include "GeneratorQtWidgetDllUi.h"

#include "Class.h"
#include "GeneratorQtWidgetDll.h"
#include "XmlHelper.h"
#include "QStringEx.h"

GeneratorQtWidgetDll::GeneratorQtWidgetDll(QWidget* parent) :
  QWidget(parent),
  ui(new GeneratorQtWidgetDllUi)
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
  files.append(":/QtWidgetDll/API/QtWidgetDll.h");
  files.append(":/QtWidgetDll/API/QtWidgetDllAPI.h");
  files.append(":/QtWidgetDll/CMakeLists.txt");
  files.append(":/QtWidgetDll/QtWidgetDll.cpp");
  files.append(":/QtWidgetDll/QtWidgetDll.ui");
  files.append(":/QtWidgetDll/QtWidgetDllDesignerPlugin.cpp");
  files.append(":/QtWidgetDll/QtWidgetDllDesignerPlugin.h");
  files.append(":/QtWidgetDll/QtWidgetDllDesignerPlugin.json");
  files.append(":/QtWidgetDll/Resources/QtWidgetDll.xml");
  files.append(":/QtWidgetDll/Resources/Resources.qrc");

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
  fileNameList.append(":/QtWidgetDll/Resources/QtWidgetDll.rc");
  fileNameList.append(":/QtWidgetDll/Resources/logo.png");

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