// created on 2017-05-10 by Ulrich Belitz

#ifndef CONVERTEREST_H
#define CONVERTEREST_H

#include <QObject>

class ConverterTest : public QObject
{
    Q_OBJECT

  private slots:
    void toHtml01();

private:
  QString testFile(const QString& testName, const QString& fileName);
};

#endif