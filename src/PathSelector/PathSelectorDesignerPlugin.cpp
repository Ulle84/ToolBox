// created on 2017-03-25 by Ulrich Belitz

#include "PathSelector.h"
#include "PathSelectorDesignerPlugin.h"

#include <QtCore/QtPlugin>

PathSelectorDesignerPlugin::PathSelectorDesignerPlugin(QObject* parent) :
  QObject(parent)
{
  initialized = false;
}

void PathSelectorDesignerPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (initialized)
  {
    return;
  }

  initialized = true;
}

bool PathSelectorDesignerPlugin::isInitialized() const
{
  return initialized;
}

QWidget* PathSelectorDesignerPlugin::createWidget(QWidget* parent)
{
  return new PathSelector(parent);
}

QString PathSelectorDesignerPlugin::name() const
{
  return "PathSelector";
}

QString PathSelectorDesignerPlugin::group() const
{
  return "Ulles Widgets";
}

QIcon PathSelectorDesignerPlugin::icon() const
{
  return QIcon(":/images/logo.png");
}

QString PathSelectorDesignerPlugin::toolTip() const
{
  return QString();
}

QString PathSelectorDesignerPlugin::whatsThis() const
{
  return QString();
}

bool PathSelectorDesignerPlugin::isContainer() const
{
  return false;
}

QString PathSelectorDesignerPlugin::domXml() const
{
  return "<widget class=\"PathSelector\" name=\"pathSelector\">\n"
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

QString PathSelectorDesignerPlugin::includeFile() const
{
  return "PathSelector.h";
}
