#include <QSettings>
#include <QMap>
#include <QMetaMethod>

#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "InstanceManager.h"
#include "Converter.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("Chuck");

  m_settings = new QSettings("Ulle", "Chuck", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  InstanceManager instanceManager;
  instanceManager.setup(Converter::configFileToJsonObject("Chuck", "settings.json"), ui->mdiArea);
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());

  delete ui;
}
