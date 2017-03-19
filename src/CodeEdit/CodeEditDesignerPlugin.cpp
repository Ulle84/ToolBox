// created on 2017-02-23 by Ulrich Belitz

#include "CodeEdit.h"
#include "CodeEditDesignerPlugin.h"

#include <QtCore/QtPlugin>

CodeEditDesignerPlugin::CodeEditDesignerPlugin(QObject* parent) :
  QObject(parent)
{
  initialized = false;
}

void CodeEditDesignerPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (initialized)
  {
    return;
  }

  initialized = true;
}

bool CodeEditDesignerPlugin::isInitialized() const
{
  return initialized;
}

QWidget* CodeEditDesignerPlugin::createWidget(QWidget* parent)
{
  return new CodeEdit(parent);
}

QString CodeEditDesignerPlugin::name() const
{
  return "CodeEdit";
}

QString CodeEditDesignerPlugin::group() const
{
  return "Ulles Widgets";
}

QIcon CodeEditDesignerPlugin::icon() const
{
  return QIcon(":/images/logo.png");
}

QString CodeEditDesignerPlugin::toolTip() const
{
  return QString();
}

QString CodeEditDesignerPlugin::whatsThis() const
{
  return QString();
}

bool CodeEditDesignerPlugin::isContainer() const
{
  return false;
}

QString CodeEditDesignerPlugin::domXml() const
{
  return "<widget class=\"CodeEdit\" name=\"codeEdit\">\n"
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

QString CodeEditDesignerPlugin::includeFile() const
{
  return "CodeEdit.h";
}
