// created on 2017-01-23 by Ulrich Belitz

#ifndef GENERATORQTWIDGETDLL_H
#define GENERATORQTWIDGETDLL_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

namespace Ui
{
  class GeneratorQtWidgetDll;
}

class GeneratorQtWidgetDll : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorQtWidgetDll(QWidget* parent = 0);
    ~GeneratorQtWidgetDll();

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
    Ui::GeneratorQtWidgetDll* ui;

    const int m_fileOffset = 1;
    const QString m_oldName = "QtWidgetDll";
};

#endif
