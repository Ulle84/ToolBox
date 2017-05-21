#include <QtCore/QtPlugin>

#include "File.h"
#include "ListEdit.h"
#include "ListEditDesignerPlugin.h"

ListEditDesignerPlugin::ListEditDesignerPlugin(QObject* parent) :
  QObject(parent)
{
  initialized = false;
}

void ListEditDesignerPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (initialized)
  {
    return;
  }

  initialized = true;
}

bool ListEditDesignerPlugin::isInitialized() const
{
  return initialized;
}

QWidget* ListEditDesignerPlugin::createWidget(QWidget* parent)
{
  return new ListEdit(parent);
}

QString ListEditDesignerPlugin::name() const
{
  return "ListEdit";
}

QString ListEditDesignerPlugin::group() const
{
  return "Ulles Widgets";
}

QIcon ListEditDesignerPlugin::icon() const
{
  return QIcon(":/images/logo.png");
}

QString ListEditDesignerPlugin::toolTip() const
{
  return QString();
}

QString ListEditDesignerPlugin::whatsThis() const
{
  return QString();
}

bool ListEditDesignerPlugin::isContainer() const
{
  return false;
}

QString ListEditDesignerPlugin::domXml() const
{
 return File(":/files/ListEdit.xml").toString();
}

QString ListEditDesignerPlugin::includeFile() const
{
  return "ListEdit.h";
}
