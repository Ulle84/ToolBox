#include <QFile>
#include <QTextStream>

#include "ui_GeneratorQtWidget.h"

#include "Class.h"
#include "GeneratorQtWidget.h"
#include "XmlHelper.h"

GeneratorQtWidget::GeneratorQtWidget(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::GeneratorQtWidget)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
}

GeneratorQtWidget::~GeneratorQtWidget()
{
  delete ui;
}

void GeneratorQtWidget::readXml(QXmlStreamReader& xml)
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

void GeneratorQtWidget::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
}

QList<QPair<QString, QString>> GeneratorQtWidget::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString oldName = "Form";
  QString newName = ui->lineEditName->text();

  QStringList files;
  files.append(":/QtWidget/Form.cpp");
  files.append(":/QtWidget/Form.h");
  files.append(":/QtWidget/Form.ui");

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

QString GeneratorQtWidget::integrationInstructions()
{
  return QString();
}

QList<QPair<QString, QString>> GeneratorQtWidget::additionalResources()
{
  return QList<QPair<QString, QString>>();
}

QString GeneratorQtWidget::directory()
{
  return QString();
}

