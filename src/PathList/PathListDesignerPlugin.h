// created on 2017-04-01 by Ulrich Belitz

#ifndef PATHLISTDESIGNERPLUGIN_H
#define PATHLISTDESIGNERPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class PathListDesignerPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "PathListDesignerPlugin.json")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

  public:
    PathListDesignerPlugin(QObject* parent = Q_NULLPTR);

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