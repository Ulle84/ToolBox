#include <QtCore/QtPlugin>

#include "File.h"
#include "QtWidgetDll.h"
#include "QtWidgetDllDesignerPlugin.h"

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
  return "Ulles Widgets";
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
 return File(":/files/QtWidgetDll.xml").toString();
}

QString QtWidgetDllDesignerPlugin::includeFile() const
{
  return "QtWidgetDll.h";
}
