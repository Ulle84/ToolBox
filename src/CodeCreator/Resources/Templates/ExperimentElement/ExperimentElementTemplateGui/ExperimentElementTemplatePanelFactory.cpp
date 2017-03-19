#include "ExperimentElementTemplatePanelFactory.h"
#include "ExperimentElementTemplatePanel.h"

Catalog::PanelFactory* createPanelFactory()
{
  return new Catalog::ExperimentElementTemplatePanelFactory();
}

namespace Catalog
{
  ExperimentElementTemplatePanelFactory::ExperimentElementTemplatePanelFactory() :
    PanelFactory()
  {
    _panelTypeList.clear();
    _panelTypeList.push_back(L"ExperimentElementTemplatePanel");
  }

  ExperimentElementTemplatePanelFactory::~ExperimentElementTemplatePanelFactory()
  {
  }

  Panel* ExperimentElementTemplatePanelFactory::createPanel(const Base::String& name, const Base::String& type, ExperimentElement* pElement, QWidget* pParent)
  {
    Panel* pR = 0;

    // Check for existence
    if (panelTypeSupported(type))
    {
      // Try to create a panel widget
      try
      {
        if (L"ExperimentElementTemplatePanel" == type)
        {
          ExperimentElementTemplatePanel* pT = new ExperimentElementTemplatePanel(name, pElement, pParent);
          pT->setWidget(pT);
          pR = pT;
        }
        else
        {
          throw Base::Exception(L"Unknown panel name.");
        }
      }
      catch (Base::Exception& ex)
      {
        Base::String text;
        text += L"Catalog::ExperimentElementTemplatePanelFactory: ";
        text += L"While creating a panel of the type >";
        text += type;
        text += L"< an error occurred: ";
        text += ex.getMessage();
        ERRLOG(Base::Warning, text);
        return 0;
      }
    }

    return pR;
  }
}
