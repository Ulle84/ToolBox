#include <QSettings>
#include <QMap>
#include <QMetaMethod>

#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Widget.h"
#include "RandomNumberGenerator.h"

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


  QJsonArray instances;

  QJsonObject instance;
  instance["class"] = "RandomNumberGenerator";
  instance["id"] = "randomNumberGenerator";
  instances.append(instance);

  instance["class"] = "Widget";
  instance["id"] = "widget0";
  instances.append(instance);

  instance["id"] = "widget1";
  instances.append(instance);

  QJsonArray connections;
  QJsonObject connection;

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

  qDebug() << configuration;

  // TODO evaluate configuration -> create instances and establish connections
  // TODO create factory method

  RandomNumberGenerator* randomNumberGenerator = new RandomNumberGenerator();
  randomNumberGenerator->start();

  QMap<QString, QObject*> map;
  map["widget1"] = new Widget(this);
  map["widget2"] = new Widget(this);
  map["randomNumberGenerator"] = randomNumberGenerator;  

  for (auto it = map.begin(); it != map.end(); ++it)
  {
    QWidget* widget = dynamic_cast<QWidget*>(it.value());

    if (widget)
      ui->mdiArea->addSubWindow(widget);
  }

  std::string source = "parameterChanged(QString,QString)";
  std::string destination = "setNewParameter(QString,QString)";

  int s = map["widget1"]->metaObject()->indexOfMethod(source.c_str());
  int d = map["widget1"]->metaObject()->indexOfMethod(destination.c_str());

  connect(map["widget1"], map["widget1"]->metaObject()->method(s), map["widget2"], map["widget2"]->metaObject()->method(d));
  connect(map["widget2"], map["widget2"]->metaObject()->method(s), map["widget1"], map["widget1"]->metaObject()->method(d));

  source = "newNumberGenerated(int)";
  destination = "setNewGeneratedNumber(int)";

  s = map["randomNumberGenerator"]->metaObject()->indexOfMethod(source.c_str());
  d = map["widget1"]->metaObject()->indexOfMethod(destination.c_str());

  connect(map["randomNumberGenerator"], map["randomNumberGenerator"]->metaObject()->method(s), map["widget2"], map["widget2"]->metaObject()->method(d));
  connect(map["randomNumberGenerator"], map["randomNumberGenerator"]->metaObject()->method(s), map["widget1"], map["widget1"]->metaObject()->method(d));  
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());

  delete ui;
}
