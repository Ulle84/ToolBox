#ifndef GeneratorAbstractFactory_H
#define GeneratorAbstractFactory_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class GeneratorAbstractFactoryUi;

class GeneratorAbstractFactory : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorAbstractFactory(QWidget* parent = 0);
    ~GeneratorAbstractFactory();

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
    GeneratorAbstractFactoryUi* ui;
};

#endif
