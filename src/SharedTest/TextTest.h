// created on 2017-03-30 by Ulrich Belitz

#ifndef TEXTEST_H
#define TEXTEST_H

#include <QObject>

class TextTest : public QObject
{
    Q_OBJECT

  private slots:
    void indentColumns1();
    void indentColumns2();

  private:
    QString testFile(const QString& testName, const QString& fileName);
};

#endif