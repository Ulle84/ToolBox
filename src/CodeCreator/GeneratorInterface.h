#ifndef GENERATORINTERFACE_H
#define GENERATORINTERFACE_H

#include <QWidget>

#include "GeneratorI.h"
#include "Interface.h"

class GeneratorInterfaceUi;

class GeneratorInterface : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorInterface(QWidget* parent = 0);
    ~GeneratorInterface();

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
    GeneratorInterfaceUi* ui;
};

#endif // GENERATORINTERFACE_H
