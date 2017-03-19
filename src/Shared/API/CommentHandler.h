#ifndef COMMENTHANDLER_H
#define COMMENTHANDLER_H

#include <QStringList>

#include "Comment.h"

#include "SharedAPI.h"

// TODO integrate functionality in CppHelper and delete this class

class SHARED_API CommentHandler
{
  public:
    CommentHandler();
    void parseAndReplaceComments(QString& code, bool cleanComments);
    void revertComments(QString& code);
    void removeComments(QString& code);

  private:
    void parseAndReplaceComments(QString& code, const Comment& comment, QStringList& comments, bool cleanComments);
    void revertComments(QString& code, const Comment& comment, const QStringList& comments);
    void removeUnnecessaryAsteriskInBlockComments();
    //void cleanComment(QString& commentContent, const Comment& comment);
    bool isCommentNecessary(const QString& commentContent);

    Comment m_lineComment1;
    Comment m_lineComment2;
    Comment m_blockComment;

    QStringList m_lineComments1;
    QStringList m_lineComments2;
    QStringList m_blockComments;
};

#endif
