#include <QSettings>
#include <QMap>
#include <QMetaMethod>

#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

#include "MainWindow.h"
#include "MainWindowUi.h"

#include "InstanceManager.h"
#include "Converter.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new MainWindowUi)
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
