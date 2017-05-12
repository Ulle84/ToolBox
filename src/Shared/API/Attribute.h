#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>

#include "SharedAPI.h"

class SHARED_API Attribute
{
  public:
    Attribute();
    Attribute(const QString& name, const QString& value);

    bool isValid();

    QString name();
    void setName(const QString& name);

    QString value();
    void setValue(const QString& value);

  private:
    QString m_name;
    QString m_value;
};

#endif
