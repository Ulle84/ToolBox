// created on 2017-03-01 by Ulrich Belitz

#ifndef FILETEST_H
#define FILETEST_H

#include <QObject>

class FileTest : public QObject
{
    Q_OBJECT

  private slots:
    void directory();
    void merge();

private:
  QString testFile(const QString& testName, const QString& fileName);
};

#endif