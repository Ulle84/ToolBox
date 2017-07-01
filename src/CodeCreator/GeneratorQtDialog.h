#ifndef GeneratorQtDialog_h
#define GeneratorQtDialog_h

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class GeneratorQtDialogUi;

class GeneratorQtDialog : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorQtDialog(QWidget* parent = 0);
    ~GeneratorQtDialog();

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
    Ui::GeneratorQtDialog* ui;
};

#endif
