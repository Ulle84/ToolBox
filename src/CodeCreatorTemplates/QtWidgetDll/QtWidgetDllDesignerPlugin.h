#ifndef QTWIDGETDLLDESIGNERPLUGIN_H
#define QTWIDGETDLLDESIGNERPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class QtWidgetDllDesignerPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "QtWidgetDllDesignerPlugin.json")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

  public:
    QtWidgetDllDesignerPlugin(QObject* parent = Q_NULLPTR);

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