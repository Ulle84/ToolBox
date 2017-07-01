#include <QFile>
#include <QTextStream>

#include "GeneratorQtDialogUi.h"

#include "Class.h"
#include "GeneratorQtDialog.h"
#include "XmlHelper.h"

GeneratorQtDialog::GeneratorQtDialog(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::GeneratorQtDialog)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
}

GeneratorQtDialog::~GeneratorQtDialog()
{
  delete ui;
}

void GeneratorQtDialog::readXml(QXmlStreamReader& xml)
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

void GeneratorQtDialog::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
}

QList<QPair<QString, QString>> GeneratorQtDialog::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString oldName = "Template";
  QString newName = ui->lineEditName->text();

  QStringList files;
  files.append(":/QtDialog/Template.cpp");
  files.append(":/QtDialog/Template.h");
  files.append(":/QtDialog/Template.ui");

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
    QString fileName = splitted.last();
    fileName.replace(oldName, newName);

    code.append(qMakePair(fileName, fileContent));
  }

  return code;
}

QString GeneratorQtDialog::integrationInstructions()
{
  return QString();
}

QList<QPair<QString, QString>> GeneratorQtDialog::additionalResources()
{
  return QList<QPair<QString, QString>>();
}

QString GeneratorQtDialog::directory()
{
  return QString();
}

