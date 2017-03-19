// created on 2017-01-23 by Ulrich Belitz

#ifndef CPPHELPER_H
#define CPPHELPER_H

#include <QString>
#include <QStringList>

#include "CppHelperAPI.h"

class CPPHELPER_API CppHelper
{
  public:
    CppHelper();
    ~CppHelper();
    void process(QString& code);
    void revert(QString& code);

  private:
    QChar peekPrevious(const QString& code, int index);
    QChar peekNext(const QString& code, int index);

    QString parseNextWord(const QString& code, int& index);
    QString parsePreviousWord(const QString& code, int& index);

    enum class ParseState
    {
      Normal,
      InsideLineComment,
      InsideBlockComment,
      InsideString
    };

    QStringList m_lineComments;
    QStringList m_blockComments;
    QStringList m_strings;

    friend class CommentAndStringExtractorTest;
};

#endif
