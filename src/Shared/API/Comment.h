// created on 2017-01-09 by Ulrich Belitz

#ifndef COMMENT_H
#define COMMENT_H

#include <QString>

#include "SharedAPI.h"

// TODO integrate functionality in CppHelper and delete this class

class SHARED_API Comment
{
  public:
    Comment();
    Comment(const QString& beginTag, const QString& endTag, const QString& replacementMap, bool endTagBelongsToComment);
    ~Comment();

    QString beginTag() const;
    QString endTag() const;
    QString replacementMap() const;
    bool endTagBelongsToComment() const;

    void setBeginTag(const QString& beginTag);
    void setEndTag(const QString& endTag);
    void setReplacementMap(const QString& replacementMap);
    void setEndTagBelongsToComment(bool endTagBelongsToComment);

  private:
    QString m_beginTag;
    QString m_endTag;
    QString m_replacementMap;
    bool m_endTagBelongsToComment;
};

#endif