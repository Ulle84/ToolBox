#ifndef GeneratorDecorator_H
#define GeneratorDecorator_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class WidgetListEditor;

class GeneratorDecoratorUi;

class GeneratorDecorator : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorDecorator(QWidget* parent = 0);
    ~GeneratorDecorator();

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
    GeneratorDecoratorUi* ui;
};

#endif // GeneratorDecorator_H
