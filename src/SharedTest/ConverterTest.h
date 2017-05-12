// created on 2017-05-10 by Ulrich Belitz

#ifndef CONVERTEREST_H
#define CONVERTEREST_H

#include <QString>
#include <QObject>

class ConverterTest : public QObject
{
    Q_OBJECT

  private slots:
    void toHtml();

  private:
    const QString m_module = "Shared";
    const QString m_category = "Converter";
};

#endif