// created on 2016-12-21 by Ulrich Belitz

#ifndef GENERATORDLL_H
#define GENERATORDLL_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class GeneratorDllUi;

class GeneratorDll : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorDll(QWidget* parent = 0);
    ~GeneratorDll();

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
    Ui::GeneratorDll* ui;
};

#endif
