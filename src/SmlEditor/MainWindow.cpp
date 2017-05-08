// created on 2017-02-23 by Ulrich Belitz

#include <QSettings>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

#include "Path.h"
#include "File.h"
#include "Converter.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("SmlEditor");

  connect(ui->treeEdit, &TreeEdit::idChanged, this, &MainWindow::onTreeEditIdChanged);
  connect(ui->treeEdit, &TreeEdit::itemRemoved, this, &MainWindow::onTreeEditItemRemoved);

  QString fileContent = File::fileToString(Path::configurationFile("SmlEditor", "content.json"));
  QJsonObject object = Converter::toJsonObject(fileContent);

  setContent(object["content"].toArray());
  ui->treeEdit->setTree(object["tree"].toObject());

  m_settings = new QSettings("Ulle", "SmlEditor", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("splitter"))
  {
    ui->splitter->restoreState(m_settings->value("splitter").toByteArray());
  }

  if (m_settings->contains("splitterSimpleHtmlEdit"))
  {
    ui->smlEdit->setSplitterState(m_settings->value("splitterSimpleHtmlEdit").toByteArray());
  }
}

MainWindow::~MainWindow()
{
  if (m_currentId >= 0)
  {
    m_textContent[m_currentId] = ui->smlEdit->text();
  }

  writeFile();
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("splitter", ui->splitter->saveState());
  m_settings->setValue("splitterSimpleHtmlEdit", ui->smlEdit->splitterState());
  delete ui;
}

void MainWindow::onTreeEditIdChanged(int id)
{
  if (m_currentId >= 0)
  {
    m_textContent[m_currentId] = ui->smlEdit->text();
  }

  m_currentId = id;
  ui->smlEdit->setText(m_textContent[m_currentId]);
}

void MainWindow::onTreeEditItemRemoved(int id)
{
  m_textContent.remove(id);
}

void MainWindow::writeFile()
{
  QFile file(Path::configurationFile("SmlEditor", "content.json"));

  if (!file.open(QIODevice::WriteOnly))
  {
    qWarning("Couldn't open save file.");
  }

  QJsonObject object;
  object["tree"] = ui->treeEdit->toJson();
  object["content"] = contentToJson();

  QJsonDocument jsonDocument(object);

  file.write(jsonDocument.toJson());
  file.close();
}

void MainWindow::setContent(const QJsonArray& json)
{
  m_textContent.clear();

  for (auto it : json)
  {
    QJsonObject object = it.toObject();
    m_textContent[object["id"].toInt()] = object["text"].toString();
  }
}

QJsonArray MainWindow::contentToJson()
{
  QJsonArray array;

  for (auto it = m_textContent.cbegin(); it != m_textContent.cend(); ++it)
  {
    if (it.value().isEmpty())
    {
      continue;
    }

    QJsonObject object;
    object["id"] = it.key();
    object["text"] = it.value();
    array.append(object);
  }

  return array;
}
