// created on 2016-12-22 by Ulrich Belitz

#include <QFile>
#include <QTextStream>

#include "GeneratorQtDesignerWidgetUi.h"

#include "Class.h"
#include "GeneratorQtDesignerWidget.h"
#include "XmlHelper.h"

GeneratorQtDesignerWidget::GeneratorQtDesignerWidget(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::GeneratorQtDesignerWidget)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
}

GeneratorQtDesignerWidget::~GeneratorQtDesignerWidget()
{
  delete ui;
}

void GeneratorQtDesignerWidget::readXml(QXmlStreamReader& xml)
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

void GeneratorQtDesignerWidget::writeXml(QXmlStreamWriter& xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
}

QList<QPair<QString, QString>> GeneratorQtDesignerWidget::generatedCode()
{
  QList<QPair<QString, QString>> code;

  QString newName = ui->lineEditName->text();

  QStringList files;
  files.append(":/files/../../CodeCreatorTemplates/QtDesignerWidget/CMakeLists.txt");
  files.append(":/files/../../CodeCreatorTemplates/QtDesignerWidget/QtDesignerWidget.cpp");
  files.append(":/files/../../CodeCreatorTemplates/QtDesignerWidget/API/QtDesignerWidget.h");
  files.append(":/files/../../CodeCreatorTemplates/QtDesignerWidget/QtDesignerWidget.ui");
  files.append(":/files/../../CodeCreatorTemplates/QtDesignerWidget/QtDesignerWidgetPlugin.cpp");
  files.append(":/files/../../CodeCreatorTemplates/QtDesignerWidget/QtDesignerWidgetPlugin.h");
  files.append(":/files/../../CodeCreatorTemplates/QtDesignerWidget/QtDesignerWidgetPlugin.json");
  files.append(":/files/../../CodeCreatorTemplates/QtDesignerWidget/Resources/Resources.qrc");

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

QString GeneratorQtDesignerWidget::integrationInstructions()
{
  return QString();
}

QList<QPair<QString, QString>> GeneratorQtDesignerWidget::additionalResources()
{
  QList<QPair<QString, QString>> list;

  QString newName = ui->lineEditName->text();

  QStringList fileNameList;
  fileNameList.append(":/files/../../CodeCreatorTemplates/QtDesignerWidget/Resources/logo.png");

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

QString GeneratorQtDesignerWidget::directory()
{
  return QString();
  //return ui->lineEditName->text();
}

