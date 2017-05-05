#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QScrollBar>
#include <QStringList>
#include <QDir>
#include <QTextStream>
#include <QDate>
#include <QLineEdit>
#include <QPlainTextEdit>

#include "ui_CodeCreator.h"

#include "CodeCreator.h"
#include "GeneratorAbstractFactory.h"
#include "GeneratorClass.h"
#include "GeneratorConsoleApplication.h"
#include "GeneratorDecorator.h"
#include "GeneratorDll.h"
#include "GeneratorExperimentElement.h"
#include "GeneratorInterface.h"
#include "GeneratorNamespace.h"
#include "GeneratorObserver.h"
#include "GeneratorQtConsoleApplication.h"
#include "GeneratorQtDialog.h"
//#include "GeneratorQtDesignerWidget.h"
#include "GeneratorQtWidget.h"
#include "GeneratorQtWidgetsApplication.h"
#include "GeneratorState.h"
#include "GeneratorTemplate.h"
#include "GeneratorQtWidgetDll.h"
#include "OptionsDialog.h"
#include "Path.h"
#include "QFontEx.h"

CodeCreator::CodeCreator(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::CodeCreator),
  m_fileName(Path::configurationFile("CodeCreator", "Settings.xml"))
{
  ui->setupUi(this);
  setWindowIcon(QIcon(":/images/logo.png"));

  m_settings = new QSettings("Ulle", "CodeCreator");

  if (m_settings->contains("windowGeometry"))
  {
    setGeometry(m_settings->value("windowGeometry").toRect());
  }

  if (m_settings->contains("splitter"))
  {
    ui->splitter->restoreState(m_settings->value("splitter").toByteArray());
  }

  initGenerators();
  readXml();
  updatePreview();

  QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>();
  for (auto it = lineEdits.begin(); it != lineEdits.end(); ++it)
  {
    (*it)->setFont(QFontEx::monospace());
  }

  QList<QPlainTextEdit*> plainTextEdits = findChildren<QPlainTextEdit*>();
  for (auto it = plainTextEdits.begin(); it != plainTextEdits.end(); ++it)
  {
    (*it)->setFont(QFontEx::monospace());
  }
}

CodeCreator::~CodeCreator()
{
  m_settings->setValue("windowGeometry", geometry());
  m_settings->setValue("splitter", ui->splitter->saveState());
  writeXml();
  delete ui;
}

void CodeCreator::initGenerators()
{
  //#] = #(#
  m_generators["AbstractFactory"     ] = new GeneratorAbstractFactory(this);
  m_generators["Class"               ] = new GeneratorClass(this);
  m_generators["ConsoleApplication"  ] = new GeneratorConsoleApplication(this);
  m_generators["Decorator"           ] = new GeneratorDecorator(this);
  m_generators["Dll"                 ] = new GeneratorDll(this);
  m_generators["ExperimentElement"   ] = new GeneratorExperimentElement(this);
  m_generators["Generator"           ] = new GeneratorTemplate(this);
  m_generators["Interface"           ] = new GeneratorInterface(this);
  m_generators["Namespace"           ] = new GeneratorNamespace(this);
  m_generators["Observer"            ] = new GeneratorObserver(this);
  m_generators["QtConsoleApplication"] = new GeneratorQtConsoleApplication(this);
  //m_generators["QtDesignerWidget"    ] = new GeneratorQtDesignerWidget    (this);
  m_generators["QtDialog"            ] = new GeneratorQtDialog(this);
  m_generators["QtWidget"            ] = new GeneratorQtWidget(this);
  m_generators["QtWidgetDll"         ] = new GeneratorQtWidgetDll(this);
  m_generators["QtWidgetsApplication"] = new GeneratorQtWidgetsApplication(this);
  m_generators["State"               ] = new GeneratorState(this);

  for (auto it = m_generators.begin(); it != m_generators.end(); it++)
  {
    if (it == m_generators.begin())
    {
      m_currentGenerator = it.value();
    }
    else
    {
      it.value()->setVisible(false);
    }

    ui->comboBoxType->addItem(it.key());
    ui->generators->layout()->addWidget(it.value());

    connect(it.value(), SIGNAL(optionsChanged()), this, SLOT(updatePreview()));
  }
}

void CodeCreator::prependInformation(QList<QPair<QString, QString>>& code)
{
  for (auto it = code.begin(); it != code.end(); it++)
  {
    if (it->first.endsWith(".h") || it->first.endsWith(".hpp") || it->first.endsWith(".cpp"))
    {
      if (m_settings->value("createAuthorComment").toBool())
      {
        QString info = "// created ";

        if (m_settings->value("includeDate").toBool())
        {
          info.append(QString("on %1 ").arg(QDate::currentDate().toString("yyyy-MM-dd")));
        }

        QString author = m_settings->value("author").toString();

        if (!author.isEmpty())
        {
          info.append(QString("by %1").arg(author));
        }

        info.append("\n\n");

        it->second.prepend(info);
      }
    }
  }
}

bool CodeCreator::generateFiles(const QList<QPair<QString, QString>>& content, GenerationType generationType)
{
  for (auto it = content.begin(); it != content.end(); it++)
  {
    if (it->first.contains("/"))
    {
      QString dirName = it->first.left(it->first.lastIndexOf("/"));

      QDir dir(ui->comboBoxFolder->currentText() + QDir::separator() + dirName);

      if (!dir.exists())
      {
        dir.mkpath(".");
      }
    }

    QString outputFileName = ui->comboBoxFolder->currentText() + QDir::separator() + it->first;
    QFile output(outputFileName);

    if (output.exists() && !m_overwriteAllFiles)
    {
      int response = QMessageBox::warning(this, tr("File already exist!"), tr("Do you want to overwrite the existing file %1?").arg(it->first), QMessageBox::No | QMessageBox::NoToAll | QMessageBox::Yes | QMessageBox::YesToAll, QMessageBox::No);

      if (response == QMessageBox::NoToAll)
      {
        return false;
      }
      else if (response == QMessageBox::No)
      {
        continue;
      }
      else if (response == QMessageBox::YesToAll)
      {
        m_overwriteAllFiles = true;
      }
    }

    if (generationType == GenerationType::CreateNewTextFile)
    {
      if (!output.open(QIODevice::WriteOnly | QIODevice::Text))
      {
        QMessageBox mb;
        mb.setText(tr("Cannot open output file %1!").arg(it->first));
        mb.exec();
        return false;
      }

      QTextStream out(&output);
      out << it->second;

      output.close();
    }
    else if (generationType == GenerationType::CopyFromFile)
    {
      QFile input(it->second);

      if (!input.exists())
      {
        QMessageBox mb;
        mb.setText(tr("Cannot open resource file %1!").arg(it->second));
        mb.exec();
        return false;
      }

      input.copy(outputFileName);
    }
  }

  return true;
}

void CodeCreator::updatePreview()
{
  QString currentFile = ui->comboBoxPreview->currentText();
  ui->comboBoxPreview->clear();

  ui->plainTextEditPreview->clear();

  GeneratorI* generator = dynamic_cast<GeneratorI*>(m_generators[ui->comboBoxType->currentText()]);

  if (!generator)
  {
    return;
  }

  QList<QPair<QString, QString>> code = generator->generatedCode();
  prependInformation(code);

  for (auto it = code.begin(); it != code.end(); it++)
  {
    ui->comboBoxPreview->addItem(it->first, it->second);
  }

  int index = ui->comboBoxPreview->findText(currentFile);

  if (index > -1)
  {
    ui->comboBoxPreview->setCurrentIndex(index);
  }

  QString integrationInstructions = generator->integrationInstructions();

  if (integrationInstructions.isEmpty())
  {
    ui->groupBoxIntegrationInstructions->setVisible(false);
  }
  else
  {
    ui->groupBoxIntegrationInstructions->setVisible(true);
    ui->plainTextEditIntegrationInstructions->setPlainText(integrationInstructions);
  }

  QList<QPair<QString, QString>> resources = generator->additionalResources();

  if (resources.isEmpty())
  {
    ui->groupBoxAdditionalResources->setVisible(false);
  }
  else
  {
    ui->groupBoxAdditionalResources->setVisible(true);
    ui->plainTextEditAdditionalResources->clear();

    for (auto& it : resources)
    {
      ui->plainTextEditAdditionalResources->appendPlainText(it.first);
    }
  }
}

void CodeCreator::on_comboBoxType_currentIndexChanged(const QString& type)
{
  if (ui->comboBoxType->count() < 1)
  {
    return;
  }

  if (type.isEmpty())
  {
    ui->comboBoxType->setCurrentIndex(0);
    return;
  }

  m_currentGenerator->setVisible(false);
  m_currentGenerator = m_generators[type];
  m_currentGenerator->setVisible(true);

  updatePreview();
}

void CodeCreator::on_pushButtonSelectFolder_clicked()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Select output folder"), ui->comboBoxFolder->currentText());

  if (directory.isEmpty())
  {
    return;
  }

  m_directories.prepend(directory);
  updateComboBoxFolders();
}

void CodeCreator::on_pushButtonGenerate_clicked()
{
  if (ui->comboBoxFolder->currentText().isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("Folder name is empty!"));
    mb.exec();
    return;
  }

  GeneratorI* generator = dynamic_cast<GeneratorI*>(m_generators[ui->comboBoxType->currentText()]);

  if (!generator)
  {
    QMessageBox mb;
    mb.setText(tr("Internal problem!"));
    mb.exec();
    return;
    return;
  }

  QList<QPair<QString, QString>> code = generator->generatedCode();
  prependInformation(code);

  m_overwriteAllFiles = false;

  generateFiles(code, GenerationType::CreateNewTextFile);
  generateFiles(generator->additionalResources(), GenerationType::CopyFromFile);

  QString directory = generator->directory();

  if (!directory.isEmpty())
  {
    QDir dir(ui->comboBoxFolder->currentText() + QDir::separator() + directory + QDir::separator() + "build");

    if (!dir.exists())
    {
      dir.mkpath(".");
    }
  }

  QMessageBox messageBox;
  messageBox.setText(tr("Creation finished!"));
  messageBox.exec();
}

void CodeCreator::on_pushButtonClearHistory_clicked()
{
  m_directories.clear();
  updateComboBoxFolders();
}

void CodeCreator::on_pushButtonOptions_clicked()
{
  OptionsDialog dialog(m_settings);
  dialog.exec();
  updatePreview();
}

bool CodeCreator::readXml()
{
  QFile file(m_fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    return false;
  }

  QXmlStreamReader xml(&file);

  if (!xml.readNextStartElement())
  {
    return false;
  }

  if (xml.name() != "Settings")
  {
    return false;
  }

  while (xml.readNextStartElement())
  {
    if (xml.name() == "SelectedType")
    {
      ui->comboBoxType->setCurrentIndex(ui->comboBoxType->findText((xml.readElementText())));
    }
    else if (xml.name() == "RecentFolders")
    {
      while (xml.readNextStartElement())
      {
        if (xml.name() == "Folder")
        {
          m_directories.append(xml.readElementText());
        }
        else
        {
          xml.skipCurrentElement();
        }
      }

      updateComboBoxFolders();
    }
    else if (xml.name() == "SelectedFolder")
    {
      ui->comboBoxFolder->setCurrentIndex(ui->comboBoxFolder->findText(xml.readElementText()));
    }
    else if (m_generators.find(xml.name().toString()) != m_generators.end())
    {
      dynamic_cast<GeneratorI*>(m_generators.find(xml.name().toString()).value())->readXml(xml);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }

  return true;
}

bool CodeCreator::writeXml()
{
  QFile file(m_fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    return false;
  }

  QXmlStreamWriter xml(&file);
  xml.setAutoFormatting(true);
  xml.setAutoFormattingIndent(2);
  xml.writeStartDocument();

  xml.writeStartElement("Settings");

  xml.writeTextElement("SelectedType", ui->comboBoxType->currentText());

  xml.writeStartElement("RecentFolders");

  for (auto it = m_directories.begin(); it != m_directories.end(); ++it)
  {
    xml.writeTextElement("Folder", *it);
  }

  xml.writeEndElement(); // RecentFolders

  xml.writeTextElement("SelectedFolder", ui->comboBoxFolder->currentText());

  // generator settings
  for (auto it = m_generators.begin(); it != m_generators.end(); ++it)
  {
    GeneratorI* generator = dynamic_cast<GeneratorI*>(it.value());

    if (generator)
    {
      xml.writeStartElement(it.key());
      generator->writeXml(xml);
      xml.writeEndElement();
    }
  }

  xml.writeEndElement(); // Settings
  xml.writeEndDocument();

  file.close();

  return true;
}

void CodeCreator::updateComboBoxFolders()
{
  m_directories.removeDuplicates();

  ui->comboBoxFolder->clear();
  ui->comboBoxFolder->insertItems(0, m_directories);
}

void CodeCreator::on_comboBoxPreview_currentIndexChanged(int index)
{
  ui->plainTextEditPreview->setPlainText(ui->comboBoxPreview->itemData(index).toString());
}
