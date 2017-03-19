#ifndef QTDESIGNERWIDGETPLUGIN_H
#define QTDESIGNERWIDGETPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class QtDesignerWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "QtDesignerWidgetPlugin.json")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

  public:
    QtDesignerWidgetPlugin(QObject* parent = Q_NULLPTR);

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