// created on 2017-03-25 by Ulrich Belitz

#ifndef PATHSELECTORDESIGNERPLUGIN_H
#define PATHSELECTORDESIGNERPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class PathSelectorDesignerPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "PathSelectorDesignerPlugin.json")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

  public:
    PathSelectorDesignerPlugin(QObject* parent = Q_NULLPTR);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget* createWidget(QWidget* parent);
    void initialize(QDesignerFormEditorInterface* core);

  private:
    bool initialized;
};

#endif