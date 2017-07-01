#ifndef GeneratorQtWidget_h
#define GeneratorQtWidget_h

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class GeneratorQtWidgetUi;

class GeneratorQtWidget : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorQtWidget(QWidget* parent = 0);
    ~GeneratorQtWidget();

    // GeneratorI
    void readXml(QXmlStreamReader& xml);
    void writeXml(QXmlStreamWriter& xml);
    QList<QPair<QString, QString> > generatedCode();
    QString integrationInstructions();
    QList<QPair<QString, QString>> additionalResources();
    QString directory();

  signals:
    void optionsChanged();

  private:
    Ui::GeneratorQtWidget* ui;
};

#endif
