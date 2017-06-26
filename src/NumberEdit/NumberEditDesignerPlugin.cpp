#include <QtCore/QtPlugin>

#include "File.h"
#include "NumberEdit.h"
#include "NumberEditDesignerPlugin.h"

NumberEditDesignerPlugin::NumberEditDesignerPlugin(QObject* parent) :
  QObject(parent)
{
  initialized = false;
}

void NumberEditDesignerPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (initialized)
  {
    return;
  }

  initialized = true;
}

bool NumberEditDesignerPlugin::isInitialized() const
{
  return initialized;
}

QWidget* NumberEditDesignerPlugin::createWidget(QWidget* parent)
{
  return new NumberEdit(parent);
}

QString NumberEditDesignerPlugin::name() const
{
  return "NumberEdit";
}

QString NumberEditDesignerPlugin::group() const
{
  return "Ulles Widgets";
}

QIcon NumberEditDesignerPlugin::icon() const
{
  return QIcon(":/images/logo.png");
}

QString NumberEditDesignerPlugin::toolTip() const
{
  return QString();
}

QString NumberEditDesignerPlugin::whatsThis() const
{
  return QString();
}

bool NumberEditDesignerPlugin::isContainer() const
{
  return false;
}

QString NumberEditDesignerPlugin::domXml() const
{
 return File(":/files/NumberEdit.xml").toString();
}

QString NumberEditDesignerPlugin::includeFile() const
{
  return "NumberEdit.h";
}
