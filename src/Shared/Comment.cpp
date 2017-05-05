// created on 2017-01-09 by Ulrich Belitz

#include "Comment.h"

Comment::Comment()
{
}

Comment::Comment(const QString& beginTag, const QString& endTag, const QString& replacementMap, bool endTagBelongsToComment) :
  m_beginTag(beginTag),
  m_endTag(endTag),
  m_replacementMap(replacementMap),
  m_endTagBelongsToComment(endTagBelongsToComment)
{
}

Comment::~Comment()
{
}

QString Comment::beginTag() const
{
  return m_beginTag;
}

QString Comment::endTag() const
{
  return m_endTag;
}

QString Comment::replacementMap() const
{
  return m_replacementMap;
}

bool Comment::endTagBelongsToComment() const
{
  return m_endTagBelongsToComment;
}

void Comment::setBeginTag(const QString& beginTag)
{
  m_beginTag = beginTag;
}

void Comment::setEndTag(const QString& endTag)
{
  m_endTag = endTag;
}

void Comment::setReplacementMap(const QString& replacementMap)
{
  m_replacementMap = replacementMap;
}

void Comment::setEndTagBelongsToComment(bool endTagBelongsToComment)
{
  m_endTagBelongsToComment = endTagBelongsToComment;
}
