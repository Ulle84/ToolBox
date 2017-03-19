#include <QDebug>

#include "QStringEx.h"

#include "CommentHandler.h"
#include "QConverter.h"

CommentHandler::CommentHandler() :
  m_lineComment1("//*", "\n", "//#%1#", false),
  m_lineComment2("//", "\n", "//%1#", false),
  m_blockComment("/*", "*/", "/*%1*/", true)
{
}

void CommentHandler::parseAndReplaceComments(QString& code, bool cleanComments)
{
  parseAndReplaceComments(code, m_lineComment1, m_lineComments1, cleanComments);
  parseAndReplaceComments(code, m_blockComment, m_blockComments, cleanComments);
  parseAndReplaceComments(code, m_lineComment2, m_lineComments2, cleanComments);

  if (cleanComments)
  {
    removeUnnecessaryAsteriskInBlockComments();
  }
}

void CommentHandler::parseAndReplaceComments(QString& code, const Comment& comment, QStringList& comments, bool cleanComments)
{
  comments.clear();

  int indexBegin = code.indexOf(comment.beginTag());
  int indexEnd = 0;
  int commmentCounter = 0;
  int searchOffset = 0;
  bool doReplacement = true;

  while (indexBegin > -1)
  {
    indexEnd = code.indexOf(comment.endTag(), indexBegin);

    if (indexEnd == -1)
    {
      indexEnd = code.length() - 1;
    }



    int length = indexEnd - indexBegin + (comment.endTagBelongsToComment() ? comment.endTag().length() : 0);

    QString commentContent = code.mid(indexBegin, length);

    if (cleanComments)
    {
      if (isCommentNecessary(commentContent))
      {
        doReplacement = true;
      }
      else
      {
        doReplacement = false;
        code.remove(indexBegin, length);
        searchOffset = 0;
      }
    }
    else
    {
      doReplacement = true;
    }

    if (doReplacement)
    {
      comments.append(commentContent);
      code.replace(indexBegin, length, comment.replacementMap().arg(commmentCounter++));
      searchOffset = comment.beginTag().length();
    }


    indexBegin = code.indexOf(comment.beginTag(), indexBegin + searchOffset);
  }
}

void CommentHandler::revertComments(QString& code)
{
  revertComments(code, m_lineComment2, m_lineComments2);
  revertComments(code, m_blockComment, m_blockComments);
  revertComments(code, m_lineComment1, m_lineComments1);


}

void CommentHandler::revertComments(QString& code, const Comment& comment, const QStringList& comments)
{
  int commentCounter = 0;
  int index = 0;

  for (auto it = comments.begin(); it != comments.end(); ++it)
  {
    QString searchString = comment.replacementMap().arg(commentCounter++);
    index = code.indexOf(searchString, index);

    if (index < 0)
    {
      // this should not happen!
      return;
    }

    code.replace(index, searchString.length(), *it);

    index += it->length();
  }
}

void CommentHandler::removeComments(QString& code)
{
  // TODO implement this functionality
}

void CommentHandler::removeUnnecessaryAsteriskInBlockComments()
{
  for (auto& it : m_blockComments)
  {
    while (it.startsWith("/***"))
    {
      it.remove(2, 1);
    }

    while (it.endsWith("**/"))
    {
      it.remove(it.size() - 2, 1);
    }

    QStringList stringList = QConverter::toStringList(it);

    for (auto& it2 : stringList)
    {
      if (it2 != stringList.first() && it2 != stringList.last())
      {
        uint16 nLeadingSpaces = QStringEx::removeLeadingSpaces(it2);

        if (it2.startsWith('*'))
        {
          it2.remove(0, 1);
          nLeadingSpaces++;
        }

        QStringEx::addLeadingSpaces(it2, nLeadingSpaces);
      }
    }

    it = QConverter::toString(stringList);
  }
}

bool CommentHandler::isCommentNecessary(const QString& commentContent)
{
  QList<QChar> unnecessaryChars;
  unnecessaryChars.append('-');
  unnecessaryChars.append(' ');
  unnecessaryChars.append('*');
  unnecessaryChars.append('/');
  unnecessaryChars.append('\n');
  unnecessaryChars.append('~');
  unnecessaryChars.append('=');

  QStringList unnecessaryComments;
  unnecessaryComments << "\\brief";
  unnecessaryComments << "\\param";
  unnecessaryComments << "Int32";
  unnecessaryComments << "constructor";
  unnecessaryComments << "destructor";
  unnecessaryComments << "end of namespace";
  unnecessaryComments << "namespace Base";
  unnecessaryComments << "namespace CU";
  unnecessaryComments << "namespace Catalog";
  unnecessaryComments << "namespace Comms";
  unnecessaryComments << "namespace Core";
  unnecessaryComments << "namespace Data";
  unnecessaryComments << "namespace ExML";
  unnecessaryComments << "namespace Exp";
  unnecessaryComments << "namespace Gui";
  unnecessaryComments << "namespace Instr";
  unnecessaryComments << "namespace Main";
  unnecessaryComments << "namespace Qt";
  unnecessaryComments << "namespace Script";
  unnecessaryComments << "namespace Store";
  unnecessaryComments << "namespace View";
  unnecessaryComments << "val";
  unnecessaryComments << "virtual";

  QString copy = commentContent;

  for (auto& it : unnecessaryComments)
  {
    copy.replace(it, "");
  }

  for (auto& it : copy)
  {
    if (!unnecessaryChars.contains(it))
    {
      return true;
    }
  }

  return false;
}

