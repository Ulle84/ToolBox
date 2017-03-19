#include "ExperimentElementTemplateFactory.h"
#include "ExperimentElementTemplate.h"
#include "Version.h"

Catalog::ExperimentElementFactory* createElementFactory()
{
  return new Catalog::ExperimentElementTemplateFactory();
}

namespace Catalog
{
  ExperimentElementTemplateFactory::ExperimentElementTemplateFactory() :
    ExperimentElementFactory(Base::String(ONT_CATALOGUEACCESS))
  {
  }

  ExperimentElementTemplateFactory::~ExperimentElementTemplateFactory()
  {
  }

  ExperimentElement* ExperimentElementTemplateFactory::createExperimentElement(const Base::String& catalog, const Base::String& type, const Base::String& name)
  {
    return new ExperimentElementTemplate(catalog, type, name);
  }
}
