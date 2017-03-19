// created on 2017-03-01 by Ulrich Belitz

#ifndef CPPHELPERTEST_H
#define CPPHELPERTEST_H

#include <QObject>

class CppHelperTest : public QObject
{
    Q_OBJECT

  private slots:
    void clean01();
    void clean02();
    void lineComments();
    void lineCommentLeadingStar();
    void blockComment();
    void string();
    void notAString();
    void removeSvnId();

  private:
    QString testFile(const QString& testName, const QString& fileName);
};

#endif