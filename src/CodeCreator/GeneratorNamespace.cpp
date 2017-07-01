#include <QFile>
#include <QTextStream>

#include "GeneratorNamespaceUi.h"

#include "Class.h"
#include "GeneratorNamespace.h"
#include "XmlHelper.h"

GeneratorNamespace::GeneratorNamespace(QWidget* parent) :
  QWidget(parent),
  ui(new GeneratorNamespaceUi)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxHeaderInSubdirectory, SIGNAL(clicked()), this, SIGNAL(optionsChanged()));
}

GeneratorNamespace::~GeneratorNamespace()
{
  delete ui;
}

void GeneratorNamespace::readXml(QXmlStreamReader& xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    if (xml.name() == "HeaderInSubdirectory")
    {
      XmlHelper::readXml(xml, ui->checkBoxHeaderInSubdirectory);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorNamespace::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  XmlHelper::writeXml(xml, "HeaderInSubdirectory", ui->checkBoxHeaderInSubdirectory);
}

QList<QPair<QString, QString>> GeneratorNamespace::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString name = ui->lineEditName->text();

  QStringList files;
  files.append(":/Namespace/Namespace.cpp");
  files.append(":/Namespace/Namespace.h");

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

    fileContent.replace("Replace", name);
    fileContent.replace(QString("Replace").toUpper(), name.toUpper());

    QStringList splitted = it->split("/");
    QString fileName = splitted.last();
    fileName.replace("Namespace", name);

    if (ui->checkBoxHeaderInSubdirectory->isChecked() && fileName.endsWith(".h"))
    {
      fileName.prepend("API/");
    }

    code.append(qMakePair(fileName, fileContent));
  }

  return code;
}

QString GeneratorNamespace::integrationInstructions()
{
  return QString();
}

QList<QPair<QString, QString>> GeneratorNamespace::additionalResources()
{
  return QList<QPair<QString, QString>>();
}

QString GeneratorNamespace::directory()
{
  return QString();
}

