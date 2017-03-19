#include "QtWidgetDll.h"
#include "QtWidgetDllDesignerPlugin.h"

#include <QtCore/QtPlugin>

QtWidgetDllDesignerPlugin::QtWidgetDllDesignerPlugin(QObject* parent) :
  QObject(parent)
{
  initialized = false;
}

void QtWidgetDllDesignerPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (initialized)
  {
    return;
  }

  initialized = true;
}

bool QtWidgetDllDesignerPlugin::isInitialized() const
{
  return initialized;
}

QWidget* QtWidgetDllDesignerPlugin::createWidget(QWidget* parent)
{
  return new QtWidgetDll(parent);
}

QString QtWidgetDllDesignerPlugin::name() const
{
  return "QtWidgetDll";
}

QString QtWidgetDllDesignerPlugin::group() const
{
  return "Ulle";
}

QIcon QtWidgetDllDesignerPlugin::icon() const
{
  return QIcon(":/images/logo.png");
}

QString QtWidgetDllDesignerPlugin::toolTip() const
{
  return QString();
}

QString QtWidgetDllDesignerPlugin::whatsThis() const
{
  return QString();
}

bool QtWidgetDllDesignerPlugin::isContainer() const
{
  return false;
}

QString QtWidgetDllDesignerPlugin::domXml() const
{
  return "<widget class=\"QtWidgetDll\" name=\"qtWidgetDll\">\n"
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

QString QtWidgetDllDesignerPlugin::includeFile() const
{
  return "QtWidgetDll.h";
}
