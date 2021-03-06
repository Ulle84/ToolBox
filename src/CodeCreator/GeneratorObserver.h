#ifndef GeneratorObserver_H
#define GeneratorObserver_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class GeneratorObserverUi;

class GeneratorObserver : public QWidget, public GeneratorI
{
    Q_OBJECT

  public:
    explicit GeneratorObserver(QWidget* parent = 0);
    ~GeneratorObserver();

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
    QString registerObserverCode();
    QString unregisterObserverCode();
    QString notifyObserversCode();
    QString testCode();

    GeneratorObserverUi* ui;
};

#endif // GeneratorObserver_H
