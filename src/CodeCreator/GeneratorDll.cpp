// created on 2016-12-21 by Ulrich Belitz

#include <QFile>
#include <QTextStream>

#include "ui_GeneratorDll.h"

#include "Class.h"
#include "GeneratorDll.h"
#include "XmlHelper.h"

GeneratorDll::GeneratorDll(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::GeneratorDll)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
}

GeneratorDll::~GeneratorDll()
{
  delete ui;
}

void GeneratorDll::readXml(QXmlStreamReader& xml)
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

void GeneratorDll::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
}

QList<QPair<QString, QString>> GeneratorDll::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString originalName = "Template";
  QString name = ui->lineEditName->text();

  QStringList files;
  files.append(":/Dll/CMakeLists.txt");
  files.append(":/Dll/Template.cpp");
  files.append(":/Dll/Template.rc");
  files.append(":/Dll/API/Template.h");
  files.append(":/Dll/API/TemplateAPI.h");

  const int fileOffset = 1;

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

    fileContent.replace(originalName, name);
    fileContent.replace(originalName.toUpper(), name.toUpper());

    QStringList splitted = it->split("/");

    for (int i = 0; i < fileOffset; ++i)
    {
      splitted.removeFirst();
    }

    QString fileName = splitted.join("/");
    fileName.replace(originalName, name);
    fileName.replace("Dll", name);

    code.append(qMakePair(fileName, fileContent));
  }

  return code;
}

QString GeneratorDll::integrationInstructions()
{
  return QString();
}

QList<QPair<QString, QString>> GeneratorDll::additionalResources()
{
  return QList<QPair<QString, QString>>();
}

QString GeneratorDll::directory()
{
  return QString();
  //return ui->lineEditName->text();
}
