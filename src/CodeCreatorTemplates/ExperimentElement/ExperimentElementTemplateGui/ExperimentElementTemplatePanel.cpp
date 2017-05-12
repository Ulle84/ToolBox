#include "ExperimentElementTemplatePanel.h"
#include "ui_ExperimentElementTemplatePanel.h"

namespace Catalog
{
  Base::String ExperimentElementTemplatePanel::parameterList[] = {L"Message"};

  ExperimentElementTemplatePanel::ExperimentElementTemplatePanel(const Base::String& name, ExperimentElement* pElement, QWidget* pParent) :
    QWidget(pParent),
    Panel(name, pElement),
    Gui::ParameterListener(pElement, parameterList, array_size(parameterList)),
    ui(new Ui::ExperimentElementTemplatePanel)
  {
    ui->setupUi(this);
  }

  ExperimentElementTemplatePanel::~ExperimentElementTemplatePanel()
  {
  }

  void ExperimentElementTemplatePanel::parameterChanged(const Gui::ParameterEvent& ev)
  {
    Base::String name = ev.getParameterName();

    if (name == L"Message")
    {
      ui->plainTextEdit->appendPlainText(Gui::qstr(ev.getValue()));
    }
  }
}
