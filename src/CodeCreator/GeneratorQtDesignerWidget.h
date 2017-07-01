// created on 2016-12-22 by Ulrich Belitz

#ifndef GENERATORQTDESIGNERWIDGET_H
#define GENERATORQTDESIGNERWIDGET_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class GeneratorQtDesignerWidgetUi;

class GeneratorQtDesignerWidget : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorQtDesignerWidget(QWidget* parent = 0);
    ~GeneratorQtDesignerWidget();

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
    Ui::GeneratorQtDesignerWidget* ui;

    const QString m_oldName = "QtDesignerWidget";
    const int m_fileOffset = 3;
};

#endif
