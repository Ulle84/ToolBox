#include <QSettings>
#include <QMap>
#include <QMetaMethod>

#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "InstanceManager.h"

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

  QJsonObject instance;
  QJsonArray instances;
  
  instance["class"] = "RandomNumberGenerator";
  instance["id"] = "randomNumberGenerator";
  instances.append(instance);

  instance["class"] = "Widget";
  instance["id"] = "widget0";
  instances.append(instance);

  instance["class"] = "Widget";
  instance["id"] = "widget1";
  instances.append(instance);

  QJsonObject connection;
  QJsonArray connections;  

  connection["source"] = "randomNumberGenerator newNumberGenerated(int)";
  connection["destination"] = "widget0 setNewGeneratedNumber(int)";
  connections.append(connection);

  connection["source"] = "randomNumberGenerator newNumberGenerated(int)";
  connection["destination"] = "widget1 setNewGeneratedNumber(int)";
  connections.append(connection);

  connection["source"] = "widget0 parameterChanged(QString,QString)";
  connection["destination"] = "widget1 setNewParameter(QString,QString)";
  connections.append(connection);

  connection["source"] = "widget1 parameterChanged(QString,QString)";
  connection["destination"] = "widget0 setNewParameter(QString,QString)";
  connections.append(connection);

  QJsonObject configuration;
  configuration["instances"] = instances;
  configuration["connections"] = connections;  

  InstanceManager instanceManager;
  instanceManager.setup(configuration, ui->mdiArea);
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());

  delete ui;
}
