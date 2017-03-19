#include <QFile>
#include <QTextStream>

#include "ui_GeneratorConsoleApplication.h"

#include "Class.h"
#include "GeneratorConsoleApplication.h"
#include "XmlHelper.h"

GeneratorConsoleApplication::GeneratorConsoleApplication(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::GeneratorConsoleApplication)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
}

GeneratorConsoleApplication::~GeneratorConsoleApplication()
{
  delete ui;
}

void GeneratorConsoleApplication::readXml(QXmlStreamReader& xml)
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

void GeneratorConsoleApplication::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
}

QList<QPair<QString, QString>> GeneratorConsoleApplication::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString name = ui->lineEditName->text();

  QStringList files;
  files.append(":/files/Templates/ConsoleApplication/CMakeLists.txt");
  files.append(":/files/Templates/ConsoleApplication/main.cpp");
  files.append(":/files/Templates/ConsoleApplication/Notes.md");

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

    fileContent.replace("ConsoleApplication", name);

    QStringList splitted = it->split("/");
    QString fileName = splitted.last();

    code.append(qMakePair(fileName, fileContent));
  }

  return code;
}

QString GeneratorConsoleApplication::integrationInstructions()
{
  return QString();
}

QList<QPair<QString, QString>> GeneratorConsoleApplication::additionalResources()
{
  return QList<QPair<QString, QString>>();
}

QString GeneratorConsoleApplication::directory()
{
  return ui->lineEditName->text();
}

