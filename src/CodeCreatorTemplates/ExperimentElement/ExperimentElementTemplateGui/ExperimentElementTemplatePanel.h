#ifndef CATALOG_EXPERIMENTELEMENTTEMPLATEPANEL_H
#define CATALOG_EXPERIMENTELEMENTTEMPLATEPANEL_H

#include "CatalogManager.h"
#include "Gui_Collection.h"

class ExperimentElementTemplatePanelUi;

namespace Catalog
{
  class ExperimentElementTemplatePanel : public QWidget, public Panel, public Gui::SettingsManager, public Gui::ParameterListener
  {
      Q_OBJECT

    public:
      ExperimentElementTemplatePanel(const Base::String& name, ExperimentElement* pElement, QWidget* pParent = 0);
      virtual ~ExperimentElementTemplatePanel();

      // implementation of Gui::ParameterListener
      virtual void parameterChanged(const Gui::ParameterEvent& ev);

    private:
      Ui::ExperimentElementTemplatePanel* ui;

      static Base::String parameterList[];
  };
}

#endif