#ifndef GENERATORTEMPLATE_H
#define GENERATORTEMPLATE_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class GeneratorTemplateUi;

class GeneratorTemplate : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorTemplate(QWidget* parent = 0);
    ~GeneratorTemplate();

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
    Ui::GeneratorTemplate* ui;

    const int m_fileOffset = 4;
};

#endif
