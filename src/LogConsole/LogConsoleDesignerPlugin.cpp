// created on 2017-04-14 by Ulrich Belitz

#include "LogConsole.h"
#include "LogConsoleDesignerPlugin.h"

#include <QtCore/QtPlugin>

LogConsoleDesignerPlugin::LogConsoleDesignerPlugin(QObject* parent) :
  QObject(parent)
{
  initialized = false;
}

void LogConsoleDesignerPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (initialized)
  {
    return;
  }

  initialized = true;
}

bool LogConsoleDesignerPlugin::isInitialized() const
{
  return initialized;
}

QWidget* LogConsoleDesignerPlugin::createWidget(QWidget* parent)
{
  return new LogConsole(parent);
}

QString LogConsoleDesignerPlugin::name() const
{
  return "LogConsole";
}

QString LogConsoleDesignerPlugin::group() const
{
  return "Ulles Widgets";
}

QIcon LogConsoleDesignerPlugin::icon() const
{
  return QIcon(":/images/logo.png");
}

QString LogConsoleDesignerPlugin::toolTip() const
{
  return QString();
}

QString LogConsoleDesignerPlugin::whatsThis() const
{
  return QString();
}

bool LogConsoleDesignerPlugin::isContainer() const
{
  return false;
}

QString LogConsoleDesignerPlugin::domXml() const
{
  return "<widget class=\"LogConsole\" name=\"logConsole\">\n"
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

QString LogConsoleDesignerPlugin::includeFile() const
{
  return "LogConsole.h";
}
