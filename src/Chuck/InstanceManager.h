#ifndef INSTANCEMANAGER_H
#define INSTANCEMANAGER_H

#include <QString>
#include <QMap>
#include <QObject>

class InstanceManager
{
  

public:
  InstanceManager();
  ~InstanceManager();

  void setup(const QString& fileName);

  QObject* object(const QString& id);

private:
  QMap<QString, QObject*> m_objects;
};

#endif