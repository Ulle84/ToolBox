#ifndef GeneratorConsoleApplication_h
#define GeneratorConsoleApplication_h

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

namespace Ui
{
  class GeneratorConsoleApplication;
}

class GeneratorConsoleApplication : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorConsoleApplication(QWidget* parent = 0);
    ~GeneratorConsoleApplication();

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
    Ui::GeneratorConsoleApplication* ui;
};

#endif
