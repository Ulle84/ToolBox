#ifndef GeneratorQtWidgetsApplication_h
#define GeneratorQtWidgetsApplication_h

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class GeneratorQtWidgetsApplicationUi;

class GeneratorQtWidgetsApplication : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorQtWidgetsApplication(QWidget* parent = 0);
    ~GeneratorQtWidgetsApplication();

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
    Ui::GeneratorQtWidgetsApplication* ui;

    const int m_fileOffset = 1;
    const QString m_oldName = "QtWidgetsApplication";
};

#endif
