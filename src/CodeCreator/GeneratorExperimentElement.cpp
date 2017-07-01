#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "GeneratorExperimentElementUi.h"

#include "Class.h"
#include "GeneratorExperimentElement.h"
#include "XmlHelper.h"

GeneratorExperimentElement::GeneratorExperimentElement(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::GeneratorExperimentElement)
{
  ui->setupUi(this);

  connect(ui->lineEditExperimentElementName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->comboBoxCatalog, SIGNAL(currentIndexChanged(int)), this, SIGNAL(optionsChanged()));
}

GeneratorExperimentElement::~GeneratorExperimentElement()
{
  delete ui;
}

void GeneratorExperimentElement::readXml(QXmlStreamReader& xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "ExperimentElementName")
    {
      XmlHelper::readXml(xml, ui->lineEditExperimentElementName);
    }
    else if (xml.name() == "Catalog")
    {
      XmlHelper::readXml(xml, ui->comboBoxCatalog);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorExperimentElement::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "ExperimentElementName", ui->lineEditExperimentElementName);
  XmlHelper::writeXml(xml, "Catalog", ui->comboBoxCatalog, false);
}

QList<QPair<QString, QString>> GeneratorExperimentElement::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString experimentElementName = ui->lineEditExperimentElementName->text();
  QString catalogName = ui->comboBoxCatalog->currentText();

  QStringList files;
  files.append(":/ExperimentElement/ExperimentElementTemplate/CMakeLists.txt");
  files.append(":/ExperimentElement/ExperimentElementTemplate/ExperimentElementTemplate.cpp");
  files.append(":/ExperimentElement/ExperimentElementTemplate/ExperimentElementTemplate.rc.template");
  files.append(":/ExperimentElement/ExperimentElementTemplate/ExperimentElementTemplateFactory.cpp");
  files.append(":/ExperimentElement/ExperimentElementTemplate/resource.h");
  files.append(":/ExperimentElement/ExperimentElementTemplate/Version.h.template");
  files.append(":/ExperimentElement/ExperimentElementTemplate/API/ExperimentElementTemplate.h");
  files.append(":/ExperimentElement/ExperimentElementTemplate/API/ExperimentElementTemplateAPI.h");
  files.append(":/ExperimentElement/ExperimentElementTemplate/API/ExperimentElementTemplateFactory.h");

  files.append(":/ExperimentElement/ExperimentElementTemplateGui/CMakeLists.txt");
  files.append(":/ExperimentElement/ExperimentElementTemplateGui/ExperimentElementTemplateGui.rc.template");
  files.append(":/ExperimentElement/ExperimentElementTemplateGui/ExperimentElementTemplateGuiAPI.h");
  files.append(":/ExperimentElement/ExperimentElementTemplateGui/ExperimentElementTemplatePanel.cpp");
  files.append(":/ExperimentElement/ExperimentElementTemplateGui/ExperimentElementTemplatePanel.h");
  files.append(":/ExperimentElement/ExperimentElementTemplateGui/ExperimentElementTemplatePanel.ui");
  files.append(":/ExperimentElement/ExperimentElementTemplateGui/ExperimentElementTemplatePanelFactory.cpp");
  files.append(":/ExperimentElement/ExperimentElementTemplateGui/ExperimentElementTemplatePanelFactory.h");
  files.append(":/ExperimentElement/ExperimentElementTemplateGui/Version.h.template");
  files.append(":/ExperimentElement/ExperimentElementTemplateGui/resource.h");

  for (auto it = files.begin(); it != files.end(); it++)
  {
    QFile file(*it);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
      continue;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    QString searchString = "ExperimentElementTemplate";
    fileContent.replace(searchString, experimentElementName);
    fileContent.replace(searchString.toUpper(), experimentElementName.toUpper());

    fileContent.replace("CatalogName", catalogName);

    QStringList splitted = it->split("/");

    for (int i = 0; i < 2; i++)
    {
      splitted.removeFirst();
    }

    QString fileName = splitted.join('/');
    fileName.replace("ExperimentElementTemplate", experimentElementName);

    code.append(qMakePair(fileName, fileContent));
  }

  return code;
}

QString GeneratorExperimentElement::integrationInstructions()
{
  QFile file(":/ExperimentElement/IntegrationInstructionsForExperimentElementTemplate.md");

  if (!file.open(QFile::ReadOnly | QFile::Text))
  {
    return QString();
  }

  QTextStream in(&file);
  QString fileContent = in.readAll();
  file.close();

  fileContent.replace("ExperimentElementTemplate", ui->lineEditExperimentElementName->text());
  fileContent.replace("CatalogName", ui->comboBoxCatalog->currentText());

  return QString(fileContent);
}

QList<QPair<QString, QString>> GeneratorExperimentElement::additionalResources()
{
  return QList<QPair<QString, QString>>();
}

QString GeneratorExperimentElement::directory()
{
  return QString();
}

