// created on 2017-02-28 by Ulrich Belitz

#ifndef CPPHELPER_H
#define CPPHELPER_H

#include <QString>
#include <QStringList>

#include "SharedAPI.h"

class SHARED_API CppHelper
{
  public:
    void shrinkCommentsAndStrings(QString& code);
    void expandCommentsAndStrings(QString& code);

    void clean(QString& code);
    void removeSvnId(QString& code);

  private:
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

    friend class CppHelperTest;
};

#endif