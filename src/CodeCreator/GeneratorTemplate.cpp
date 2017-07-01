#include <QFile>
#include <QTextStream>

#include "GeneratorTemplateUi.h"

#include "GeneratorTemplate.h"
#include "XmlHelper.h"

GeneratorTemplate::GeneratorTemplate(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::GeneratorTemplate)
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
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorTemplate::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
}

QList<QPair<QString, QString>> GeneratorTemplate::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString generatorName = QString("Generator%1").arg(ui->lineEditName->text());
  QString generatorTemplate = "GeneratorTemplate";

  QStringList files;
  files.append(":/Generator/GeneratorTemplate.h");
  files.append(":/Generator/GeneratorTemplate.cpp");
  files.append(":/Generator/GeneratorTemplate.ui");

  const int fileOffset = 2;

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

    fileContent.replace(generatorTemplate, generatorName);
    fileContent.replace(generatorTemplate.toUpper(), generatorName.toUpper());

    QStringList splitted = it->split("/");

    for (int i = 0; i < fileOffset; ++i)
    {
      splitted.removeFirst();
    }

    QString fileName = splitted.join("/");
    fileName.replace(generatorTemplate, generatorName);

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

