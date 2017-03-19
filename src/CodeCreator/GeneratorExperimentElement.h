#ifndef GeneratorExperimentElement_h
#define GeneratorExperimentElement_h

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

namespace Ui
{
  class GeneratorExperimentElement;
}

class GeneratorExperimentElement : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorExperimentElement(QWidget* parent = 0);
    ~GeneratorExperimentElement();

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
    Ui::GeneratorExperimentElement* ui;
};

#endif
