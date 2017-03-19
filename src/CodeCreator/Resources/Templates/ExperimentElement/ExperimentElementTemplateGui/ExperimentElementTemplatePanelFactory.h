#ifndef CATALOG_EXPERIMENTELEMENTTEMPLATEPANELFACTORY_H
#define CATALOG_EXPERIMENTELEMENTTEMPLATEPANELFACTORY_H

#include "CatalogManager.h"
#include "ExperimentElementTemplateGuiAPI.h"

extern "C"
{
  CATALOG_EXPERIMENTELEMENTTEMPLATEGUI_API Catalog::PanelFactory* createPanelFactory();
}

namespace Catalog
{
  class ExperimentElementTemplatePanelFactory : public PanelFactory
  {
    public:
      ExperimentElementTemplatePanelFactory();
      virtual ~ExperimentElementTemplatePanelFactory();

      virtual Panel* createPanel(const Base::String& name, const Base::String& type, ExperimentElement* pElement, QWidget* pParent);
  };
}

#endif