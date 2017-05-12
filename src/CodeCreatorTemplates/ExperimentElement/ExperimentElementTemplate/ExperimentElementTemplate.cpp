#include "ExperimentElementTemplate.h"

namespace Catalog
{
  ExperimentElementTemplate::ExperimentElementTemplate(const Base::String& catalog, const Base::String& type, const Base::String& name) :
    Exp::ExperimentElement(catalog, type, name)
  {
  }

  ExperimentElementTemplate::~ExperimentElementTemplate()
  {
  }

  void ExperimentElementTemplate::setup()
  {
    /**
      Deployment parameters

      @deployment Standard_Instrument
         The name of the standard instrument.
    */
    DEPLOYMENT_PARAMETER(L"Standard_Instrument");

    /**
      @parameter Message [String]
        This parameter holds a message.
    */
    STRING_PARAM(L"Message", MESSAGE, L"", &ExperimentElementTemplate::messageChanged, INHIBIT);

    // TODO further implementation
  }

  void ExperimentElementTemplate::initialize()
  {
    markAsPrimaryDeploymentParameter(L"Standard_Instrument");
    _primaryDeploymentParameterName = L"Standard_Instrument";

    // TODO further implementation
  }

  void ExperimentElementTemplate::messageChanged(Base::Value* pNew, Bool rawValueSupported, Base::RawValue newRaw)
  {
    // TODO implementation
  }

  void ExperimentElementTemplate::upload(Base::String primaryDeploymentParameter)
  {
    // TODO further implementation
    setParameter(L"Message", Base::VString(L"uploading ExperimentElementTemplate"));
    ExperimentElement::upload(primaryDeploymentParameter);
  }

  void ExperimentElementTemplate::launch()
  {
    // TODO further implementation
    ExperimentElement::launch();
  }

  void ExperimentElementTemplate::incident(Uint32 type, Base::String instrumentName, std::map<Base::String, Base::Value*> params)
  {
    // TODO implement handling of incident event - depending on type
  }
}
