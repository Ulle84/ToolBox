#ifndef INSTANCEMANAGER_H
#define INSTANCEMANAGER_H

#include <QString>
#include <QMap>
#include <QObject>

class QMdiArea;
class QJSonObject;

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
    void connect(const QString& source, const QString& destination);

    QMap<QString, QObject*> m_objects;
};

#endif