// created on 2017-03-15 by Ulrich Belitz

#include "SmlEdit.h"
#include "SmlEditDesignerPlugin.h"

#include <QtCore/QtPlugin>

SmlEditDesignerPlugin::SmlEditDesignerPlugin(QObject* parent) :
  QObject(parent)
{
  initialized = false;
}

void SmlEditDesignerPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (initialized)
  {
    return;
  }

  initialized = true;
}

bool SmlEditDesignerPlugin::isInitialized() const
{
  return initialized;
}

QWidget* SmlEditDesignerPlugin::createWidget(QWidget* parent)
{
  return new SmlEdit(parent);
}

QString SmlEditDesignerPlugin::name() const
{
  return "SmlEdit";
}

QString SmlEditDesignerPlugin::group() const
{
  return "Ulles Widgets";
}

QIcon SmlEditDesignerPlugin::icon() const
{
  return QIcon(":/images/logo.png");
}

QString SmlEditDesignerPlugin::toolTip() const
{
  return QString();
}

QString SmlEditDesignerPlugin::whatsThis() const
{
  return QString();
}

bool SmlEditDesignerPlugin::isContainer() const
{
  return false;
}

QString SmlEditDesignerPlugin::domXml() const
{
  return "<widget class=\"SmlEdit\" name=\"smlEdit\">\n"
         " <property name=\"geometry\">\n"
         "  <rect>\n"
         "   <x>0</x>\n"
         "   <y>0</y>\n"
         "   <width>100</width>\n"
         "   <height>100</height>\n"
         "  </rect>\n"
         " </property>\n"
         "</widget>\n";
}

QString SmlEditDesignerPlugin::includeFile() const
{
  return "SmlEdit.h";
}
