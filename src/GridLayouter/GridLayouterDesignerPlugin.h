// created on 2017-04-15 by Ulrich Belitz

#ifndef GRIDLAYOUTERDESIGNERPLUGIN_H
#define GRIDLAYOUTERDESIGNERPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class GridLayouterDesignerPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "GridLayouterDesignerPlugin.json")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

  public:
    GridLayouterDesignerPlugin(QObject* parent = Q_NULLPTR);

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