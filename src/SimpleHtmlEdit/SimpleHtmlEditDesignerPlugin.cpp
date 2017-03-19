// created on 2017-03-15 by Ulrich Belitz

#include "SimpleHtmlEdit.h"
#include "SimpleHtmlEditDesignerPlugin.h"

#include <QtCore/QtPlugin>

SimpleHtmlEditDesignerPlugin::SimpleHtmlEditDesignerPlugin(QObject* parent) :
  QObject(parent)
{
  initialized = false;
}

void SimpleHtmlEditDesignerPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (initialized)
  {
    return;
  }

  initialized = true;
}

bool SimpleHtmlEditDesignerPlugin::isInitialized() const
{
  return initialized;
}

QWidget* SimpleHtmlEditDesignerPlugin::createWidget(QWidget* parent)
{
  return new SimpleHtmlEdit(parent);
}

QString SimpleHtmlEditDesignerPlugin::name() const
{
  return "SimpleHtmlEdit";
}

QString SimpleHtmlEditDesignerPlugin::group() const
{
  return "Ulle";
}

QIcon SimpleHtmlEditDesignerPlugin::icon() const
{
  return QIcon(":/images/logo.png");
}

QString SimpleHtmlEditDesignerPlugin::toolTip() const
{
  return QString();
}

QString SimpleHtmlEditDesignerPlugin::whatsThis() const
{
  return QString();
}

bool SimpleHtmlEditDesignerPlugin::isContainer() const
{
  return false;
}

QString SimpleHtmlEditDesignerPlugin::domXml() const
{
  return "<widget class=\"SimpleHtmlEdit\" name=\"simpleHtmlEdit\">\n"
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

QString SimpleHtmlEditDesignerPlugin::includeFile() const
{
  return "SimpleHtmlEdit.h";
}
