#ifndef INSTANCEMANAGER_H
#define INSTANCEMANAGER_H

#include <QString>
#include <QMap>
#include <QObject>

class QMdiArea;

class InstanceManager
{
  

public:
  InstanceManager();
  ~InstanceManager();

  void setup(const QString& fileName);
  void setup(const QJsonObject& configuration, QMdiArea* mdiArea);

  QObject* object(const QString& id);
  QObject* createObject(const QString& className, const QString& id);

private:
  QMap<QString, QObject*> m_objects;
};

#endif