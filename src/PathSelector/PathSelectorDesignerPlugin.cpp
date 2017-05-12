// created on 2017-03-25 by Ulrich Belitz

#include <QtCore/QtPlugin>

#include "PathSelector.h"
#include "PathSelectorDesignerPlugin.h"
#include "File.h"

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
  return File(":/files/PathSelector.xml").toString();
}

QString PathSelectorDesignerPlugin::includeFile() const
{
  return "PathSelector.h";
}
