#ifndef SHAREDRESOURCES_H
#define SHAREDRESOURCES_H

#include <QString>

#include "SharedResourcesAPI.h"

namespace SharedResources
{
  QString SHAREDRESOURCES_API toString(const QString& resource);
  QString SHAREDRESOURCES_API defaultStyleSheet();
  QString SHAREDRESOURCES_API testSmlCode();
}

#endif
