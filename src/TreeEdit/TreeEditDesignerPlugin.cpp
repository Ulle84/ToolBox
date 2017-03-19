// created on 2017-03-06 by Ulrich Belitz

#include "TreeEdit.h"
#include "TreeEditDesignerPlugin.h"

#include <QtCore/QtPlugin>

TreeEditDesignerPlugin::TreeEditDesignerPlugin(QObject* parent) :
  QObject(parent)
{
  initialized = false;
}

void TreeEditDesignerPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (initialized)
  {
    return;
  }

  initialized = true;
}

bool TreeEditDesignerPlugin::isInitialized() const
{
  return initialized;
}

QWidget* TreeEditDesignerPlugin::createWidget(QWidget* parent)
{
  return new TreeEdit(parent);
}

QString TreeEditDesignerPlugin::name() const
{
  return "TreeEdit";
}

QString TreeEditDesignerPlugin::group() const
{
  return "Ulle";
}

QIcon TreeEditDesignerPlugin::icon() const
{
  return QIcon(":/images/logo.png");
}

QString TreeEditDesignerPlugin::toolTip() const
{
  return QString();
}

QString TreeEditDesignerPlugin::whatsThis() const
{
  return QString();
}

bool TreeEditDesignerPlugin::isContainer() const
{
  return false;
}

QString TreeEditDesignerPlugin::domXml() const
{
  return "<widget class=\"TreeEdit\" name=\"treeEdit\">\n"
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

QString TreeEditDesignerPlugin::includeFile() const
{
  return "TreeEdit.h";
}
