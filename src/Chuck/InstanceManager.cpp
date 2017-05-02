#include <QMdiArea>

#include "InstanceManager.h"

#include "RandomNumberGenerator.h"
#include "Widget.h"



InstanceManager::InstanceManager()
{

}

InstanceManager::~InstanceManager()
{

}

QObject* InstanceManager::object(const QString& id)
{
  return m_objects[id];
}

void InstanceManager::setup(const QString& fileName)
{
  // TODO
}

void InstanceManager::setup(const QJsonObject& configuration, QMdiArea* mdiArea)
{
  // TODO

  //RandomNumberGenerator* randomNumberGenerator = new RandomNumberGenerator();
  //randomNumberGenerator->start();
  //
  //QMap<QString, QObject*> map;
  //map["widget1"] = new Widget(this);
  //map["widget2"] = new Widget(this);
  //map["randomNumberGenerator"] = randomNumberGenerator;
  //
  //for (auto it = map.begin(); it != map.end(); ++it)
  //{
  //  QWidget* widget = dynamic_cast<QWidget*>(it.value());
  //
  //  if (widget)
  //    ui->mdiArea->addSubWindow(widget);
  //}
  //
  //std::string source = "parameterChanged(QString,QString)";
  //std::string destination = "setNewParameter(QString,QString)";
  //
  //int s = map["widget1"]->metaObject()->indexOfMethod(source.c_str());
  //int d = map["widget1"]->metaObject()->indexOfMethod(destination.c_str());
  //
  //connect(map["widget1"], map["widget1"]->metaObject()->method(s), map["widget2"], map["widget2"]->metaObject()->method(d));
  //connect(map["widget2"], map["widget2"]->metaObject()->method(s), map["widget1"], map["widget1"]->metaObject()->method(d));
  //
  //source = "newNumberGenerated(int)";
  //destination = "setNewGeneratedNumber(int)";
  //
  //s = map["randomNumberGenerator"]->metaObject()->indexOfMethod(source.c_str());
  //d = map["widget1"]->metaObject()->indexOfMethod(destination.c_str());
  //
  //connect(map["randomNumberGenerator"], map["randomNumberGenerator"]->metaObject()->method(s), map["widget2"], map["widget2"]->metaObject()->method(d));
  //connect(map["randomNumberGenerator"], map["randomNumberGenerator"]->metaObject()->method(s), map["widget1"], map["widget1"]->metaObject()->method(d));
}



QObject* InstanceManager::createObject(const QString& className, const QString& id)
{
  if (m_objects.contains(id))
  {
    // TODO define own exception type
    throw std::exception(QString("instance with the ID %1 already exists").arg(id).toStdString().c_str());
  }

  QObject* object = nullptr;

  if (className == "RandomNumberGenerator")
  {
    object = new RandomNumberGenerator();
  }
  else if (className == "RandomNumberGenerator")
  {
    object = new Widget();    
  }

  if (!object)
  {
    // TODO define own exception type
    throw std::exception(QString("instance of class %1 could not be created").arg(className).toStdString().c_str());
  }

  m_objects[id] = object;

  return object;
}