#ifndef CATALOG_EXPERIMENTELEMENTTEMPLATE_H
#define CATALOG_EXPERIMENTELEMENTTEMPLATE_H

#include "Exp.h"
#include "ExperimentElementTemplateAPI.h"

namespace Catalog
{
  class CATALOG_EXPERIMENTELEMENTTEMPLATE_API ExperimentElementTemplate : public Exp::ExperimentElement
  {
    public:
      ExperimentElementTemplate(const Base::String& catalog, const Base::String& type, const Base::String& name);
      virtual ~ExperimentElementTemplate();

      virtual void setup();
      virtual void initialize();

      virtual void upload(Base::String primaryDeploymentParameter = L"");
      virtual void launch();

      void incident(Uint32 type, Base::String instrumentName, std::map<Base::String, Base::Value*> params);

      enum Parameters
      {
        MESSAGE = 0
      };

      void messageChanged(Base::Value* pNew, Bool rawValueSupported, Base::RawValue newRaw);
  };
}

#endif
