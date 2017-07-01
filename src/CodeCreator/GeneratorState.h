#ifndef GeneratorState_H
#define GeneratorState_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class WidgetListEditor;

class GeneratorStateUi;

class GeneratorState : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorState(QWidget* parent = 0);
    ~GeneratorState();

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
    GeneratorStateUi* ui;
};

#endif // GeneratorState_H
