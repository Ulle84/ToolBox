// created on 2017-04-15 by Ulrich Belitz

#include "GridLayouter.h"
#include "GridLayouterDesignerPlugin.h"

#include <QtCore/QtPlugin>

GridLayouterDesignerPlugin::GridLayouterDesignerPlugin(QObject* parent) :
  QObject(parent)
{
  initialized = false;
}

void GridLayouterDesignerPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (initialized)
  {
    return;
  }

  initialized = true;
}

bool GridLayouterDesignerPlugin::isInitialized() const
{
  return initialized;
}

QWidget* GridLayouterDesignerPlugin::createWidget(QWidget* parent)
{
  return new GridLayouter(parent);
}

QString GridLayouterDesignerPlugin::name() const
{
  return "GridLayouter";
}

QString GridLayouterDesignerPlugin::group() const
{
  return "Ulles Widgets";
}

QIcon GridLayouterDesignerPlugin::icon() const
{
  return QIcon(":/images/logo.png");
}

QString GridLayouterDesignerPlugin::toolTip() const
{
  return QString();
}

QString GridLayouterDesignerPlugin::whatsThis() const
{
  return QString();
}

bool GridLayouterDesignerPlugin::isContainer() const
{
  return true;
}

QString GridLayouterDesignerPlugin::domXml() const
{
  return "<widget class=\"GridLayouter\" name=\"gridLayouter\">\n"
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

QString GridLayouterDesignerPlugin::includeFile() const
{
  return "GridLayouter.h";
}
