#ifndef GeneratorQtConsoleApplication_h
#define GeneratorQtConsoleApplication_h

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

namespace Ui
{
  class GeneratorQtConsoleApplication;
}

class GeneratorQtConsoleApplication : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorQtConsoleApplication(QWidget* parent = 0);
    ~GeneratorQtConsoleApplication();

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
    Ui::GeneratorQtConsoleApplication* ui;

    const int m_fileOffset = 3;
    const QString m_oldName = "QtConsoleApplication";
};

#endif
