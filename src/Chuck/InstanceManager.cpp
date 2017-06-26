#include <QMdiArea>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QMetaMethod>

#include "InstanceManager.h"

#include "RandomNumberGenerator.h"
#include "Widget.h"
#include "NumberDisplay.h"

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

  QJsonArray instances = configuration["instances"].toArray();
  QJsonArray connections = configuration["connections"].toArray();

  for (auto it = instances.begin(); it != instances.end(); ++it)
  {
    QJsonObject instance = it->toObject();

    QString className = instance["class"].toString();
    QString id = instance["id"].toString();

    QObject* object = createObject(className, id);

    if (QWidget* widget = dynamic_cast<QWidget*>(object))
    {
      mdiArea->addSubWindow(widget);
    }
  }

  for (auto it = connections.begin(); it != connections.end(); ++it)
  {
    QJsonObject connection = it->toObject();

    QString source = connection["source"].toString();
    QString destination = connection["destination"].toString();

    connect(source, destination);
  }

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

void InstanceManager::connect(const QString& source, const QString& destination)
{
  QStringList sourceInformation = source.split(' ');
  QStringList destinationInformation = destination.split(' ');

  if (sourceInformation.size() != 2 || destinationInformation.size() != 2)
  {
    throw std::exception("connect parameters are wrong");
  }

  // TODO source/destination vs. sender/receiver -> see how this is described in qt documentation!
  if (!m_objects.contains(sourceInformation[0]))
  {
    throw std::exception("sender does not exist");
  }

  if (!m_objects.contains(destinationInformation[0]))
  {
    throw std::exception("receiver does not exist");
  }

  int sourceIndex = m_objects[sourceInformation[0]]->metaObject()->indexOfMethod(sourceInformation[1].toStdString().c_str());

  if (sourceIndex < 0)
  {
    throw std::exception("signal does not exist");
  }

  int destinationIndex = m_objects[destinationInformation[0]]->metaObject()->indexOfMethod(destinationInformation[1].toStdString().c_str());

  if (sourceIndex < 0)
  {
    throw std::exception("slot does not exist");
  }

  bool success = QObject::connect(m_objects[sourceInformation[0]], m_objects[sourceInformation[0]]->metaObject()->method(sourceIndex),
                                  m_objects[destinationInformation[0]], m_objects[destinationInformation[0]]->metaObject()->method(destinationIndex));
  bool stopHere = true;
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
  else if (className == "Widget")
  {
    object = new Widget();
  }
  else if (className == "NumberDisplay")
  {
    object = new NumberDisplay();
  }

  if (!object)
  {
    // TODO define own exception type
    throw std::exception(QString("instance of class %1 could not be created").arg(className).toStdString().c_str());
  }

  if (QThread* thread = dynamic_cast<QThread*>(object))
  {
    thread->start();
  }

  m_objects[id] = object;

  return object;
}