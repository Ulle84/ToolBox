#include <QFile>
#include <QTextStream>

#include "GeneratorTemplateUi.h"

#include "Class.h"
#include "GeneratorTemplate.h"
#include "XmlHelper.h"

GeneratorTemplate::GeneratorTemplate(QWidget* parent) :
  QWidget(parent),
  ui(new GeneratorTemplateUi)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
}

GeneratorTemplate::~GeneratorTemplate()
{
  delete ui;
}

void GeneratorTemplate::readXml(QXmlStreamReader& xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    // TODO add further members here
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorTemplate::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  // TODO add further members here
}

QList<QPair<QString, QString>> GeneratorTemplate::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString oldName = "Template";
  QString newName = ui->lineEditName->text();

  QStringList files;
  files.append(":/files/Templates/Template/Template.cpp");
  files.append(":/files/Templates/Template/Template.h");

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

    fileContent.replace(oldName, newName);
    fileContent.replace(oldName.toUpper(), newName.toUpper());

    QStringList splitted = it->split("/");

    for (int i = 0; i < m_fileOffset; ++i)
    {
      splitted.removeFirst();
    }

    QString fileName = splitted.join("/");
    fileName.replace(oldName, newName);

    code.append(qMakePair(fileName, fileContent));
  }

  return code;
}

QString GeneratorTemplate::integrationInstructions()
{
  return QString();
}

QList<QPair<QString, QString>> GeneratorTemplate::additionalResources()
{
  return QList<QPair<QString, QString>>();
}

QString GeneratorTemplate::directory()
{
  return QString();
}