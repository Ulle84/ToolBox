#ifndef CATALOG_EXPERIMENTELEMENTTEMPLATEFACTORY_H
#define CATALOG_EXPERIMENTELEMENTTEMPLATEFACTORY_H

#include "CatalogManager.h"
#include "ExperimentElementTemplateAPI.h"

extern "C"
{
  CATALOG_EXPERIMENTELEMENTTEMPLATE_API Catalog::ExperimentElementFactory* createElementFactory();
}

namespace Catalog
{
  class CATALOG_EXPERIMENTELEMENTTEMPLATE_API ExperimentElementTemplateFactory : public ExperimentElementFactory
  {
    public:
      ExperimentElementTemplateFactory();
      virtual ~ExperimentElementTemplateFactory();

      virtual ExperimentElement* createExperimentElement(const Base::String& catalog, const Base::String& type, const Base::String& name);
  };
}

#endif