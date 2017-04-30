#include "InstanceManager.h"

#include <QPushButton>

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

  m_objects["pushButton"] = new QPushButton("push me!");
}