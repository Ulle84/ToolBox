#ifndef GeneratorNamespace_h
#define GeneratorNamespace_h

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class GeneratorNamespaceUi;

class GeneratorNamespace : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorNamespace(QWidget* parent = 0);
    ~GeneratorNamespace();

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
    GeneratorNamespaceUi* ui;
};

#endif
