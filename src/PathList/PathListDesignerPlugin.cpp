// created on 2017-04-01 by Ulrich Belitz

#include "PathList.h"
#include "PathListDesignerPlugin.h"

#include <QtCore/QtPlugin>

PathListDesignerPlugin::PathListDesignerPlugin(QObject* parent) :
  QObject(parent)
{
  initialized = false;
}

void PathListDesignerPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (initialized)
  {
    return;
  }

  initialized = true;
}

bool PathListDesignerPlugin::isInitialized() const
{
  return initialized;
}

QWidget* PathListDesignerPlugin::createWidget(QWidget* parent)
{
  return new PathList(parent);
}

QString PathListDesignerPlugin::name() const
{
  return "PathList";
}

QString PathListDesignerPlugin::group() const
{
  return "Ulles Widgets";
}

QIcon PathListDesignerPlugin::icon() const
{
  return QIcon(":/images/logo.png");
}

QString PathListDesignerPlugin::toolTip() const
{
  return QString();
}

QString PathListDesignerPlugin::whatsThis() const
{
  return QString();
}

bool PathListDesignerPlugin::isContainer() const
{
  return false;
}

QString PathListDesignerPlugin::domXml() const
{
  return "<widget class=\"PathList\" name=\"pathList\">\n"
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

QString PathListDesignerPlugin::includeFile() const
{
  return "PathList.h";
}
