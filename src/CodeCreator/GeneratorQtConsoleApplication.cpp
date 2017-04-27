#include <QFile>
#include <QTextStream>

#include "ui_GeneratorQtConsoleApplication.h"

#include "Class.h"
#include "GeneratorQtConsoleApplication.h"
#include "XmlHelper.h"

GeneratorQtConsoleApplication::GeneratorQtConsoleApplication(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::GeneratorQtConsoleApplication)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
}

GeneratorQtConsoleApplication::~GeneratorQtConsoleApplication()
{
  delete ui;
}

void GeneratorQtConsoleApplication::readXml(QXmlStreamReader& xml)
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

void GeneratorQtConsoleApplication::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
}

QList<QPair<QString, QString>> GeneratorQtConsoleApplication::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString newName = ui->lineEditName->text();

  QStringList files;
  files.append(":/files/Templates/QtConsoleApplication/CMakeLists.txt");
  files.append(":/files/Templates/QtConsoleApplication/main.cpp");

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

QString GeneratorQtConsoleApplication::integrationInstructions()
{
  return QString();
}

QList<QPair<QString, QString>> GeneratorQtConsoleApplication::additionalResources()
{
  return QList<QPair<QString, QString>>();
}

QString GeneratorQtConsoleApplication::directory()
{
  return QString();
  //return ui->lineEditName->text();
}

