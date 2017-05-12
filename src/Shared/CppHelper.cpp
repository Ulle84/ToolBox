// created on 2017-02-28 by Ulrich Belitz

#include "CppHelper.h"
#include "QStringEx.h"

void CppHelper::shrinkCommentsAndStrings(QString& code)
{
  ParseState parseState = ParseState::Normal;

  int startIndex = 0;

  for (int i = 0; i < code.length(); ++i)
  {
    if (parseState == ParseState::Normal)
    {
      if (code[i] == '"' && QStringEx::peekPrevious(code, i) != '\\')
      {
        startIndex = i + 1;
        parseState = ParseState::InsideString;
        continue;
      }
      else if (code[i] == '/')
      {
        if (QStringEx::peekNext(code, i) == '/')
        {
          startIndex = i + 2;
          parseState = ParseState::InsideLineComment;
          ++i;
          continue;
        }
        else if (QStringEx::peekNext(code, i) == '*')
        {
          startIndex = i + 2;
          parseState = ParseState::InsideBlockComment;
          ++i;
          continue;
        }
      }

      /*else if (code[i] == '\n' && QStringEx::peekNext(code, i) == '\n' && QStringEx::peekNext(code, i, 2) == '\n')
      {
        code.remove(i, 1);
      }*/
    }
    else if (parseState == ParseState::InsideString)
    {
      if (code[i] == '"' && QStringEx::peekPrevious(code, i) != '\\')
      {
        m_strings.append(code.mid(startIndex, i - startIndex));
        code.remove(startIndex, i - startIndex);
        i = startIndex;
        parseState = ParseState::Normal;
        continue;
      }
    }
    else if (parseState == ParseState::InsideLineComment)
    {
      // TODO check if content of line comment is necessary - see CommentHandler
      if (code[i] == '\n')
      {
        m_lineComments.append(code.mid(startIndex, i - startIndex));
        code.remove(startIndex, i - startIndex);
        i = startIndex;
        parseState = ParseState::Normal;
        continue;
      }
      else if (i == code.length() - 1)
      {
        m_lineComments.append(code.mid(startIndex, i - startIndex + 1));
        code.remove(startIndex, i - startIndex + 1);
        i = startIndex;
        parseState = ParseState::Normal;
        continue;
      }
    }
    else if (parseState == ParseState::InsideBlockComment)
    {
      // TODO check if content of block comment is necessary - see CommentHandler
      if (code[i] == '*' && QStringEx::peekNext(code, i) == '/')
      {
        m_blockComments.append(code.mid(startIndex, i - startIndex));
        code.remove(startIndex, i - startIndex);
        i = startIndex;
        parseState = ParseState::Normal;
        continue;
      }
    }
  }
}

void CppHelper::expandCommentsAndStrings(QString& code)
{
  for (int i = 0; i < code.length(); ++i)
  {
    if (code[i] == '/')
    {
      if (QStringEx::peekNext(code, i) == '/')
      {
        // line comment
        code.insert(i + 2, m_lineComments.first());
        i += m_lineComments.first().length() + 1;
        m_lineComments.removeFirst();
      }
      else if (QStringEx::peekNext(code, i) == '*' && QStringEx::peekNext(code, i, 2) == '*' && QStringEx::peekNext(code, i, 3) == '/')
      {
        // block comment
        code.insert(i + 2, m_blockComments.first());
        i += m_blockComments.first().length() + 3;
        m_blockComments.removeFirst();
      }
    }
    else if (code[i] == '"' && QStringEx::peekNext(code, i) == '"')
    {
      // string
      code.insert(i + 1, m_strings.first());
      i += m_strings.first().length() + 1;
      m_strings.removeFirst();
    }
  }
}

void CppHelper::clean(QString& code)
{
  ParseState parseState = ParseState::Normal;

  int startIndex = 0;

  for (int i = 0; i < code.length(); ++i)
  {
    if (parseState == ParseState::Normal)
    {
      if (code[i] == '"' && QStringEx::peekPrevious(code, i) != '\\')
      {
        parseState = ParseState::InsideString;
        continue;
      }
      else if (code[i] == '/')
      {
        if (QStringEx::peekNext(code, i) == '/')
        {
          parseState = ParseState::InsideLineComment;
          ++i;
          continue;
        }
        else if (QStringEx::peekNext(code, i) == '*')
        {
          parseState = ParseState::InsideBlockComment;
          ++i;
          continue;
        }
      }
      else if (code[i] == '\n' && QStringEx::peekNext(code, i) == '\n' && QStringEx::peekNext(code, i, 2) == '\n')
      {
        // remove double empty line
        code.remove(i, 1);
        --i;
      }
      else if (code[i] == '{' && QStringEx::peekNext(code, i) == '\n' && QStringEx::peekNext(code, i, 2) == '\n')
      {
        // remove empty line after opened block
        code.remove(i + 1, 1);
        --i;
      }
      else if (code[i] == '\n' && QStringEx::peekNext(code, i) == '\n' && QStringEx::peekNextNonWhitespace(code, i) == '}')
      {
        // remove empty line before closed block
        code.remove(i, 1);
        --i;
      }
    }
    else if (parseState == ParseState::InsideString)
    {
      if (code[i] == '"' && QStringEx::peekPrevious(code, i) != '\\')
      {
        parseState = ParseState::Normal;
        continue;
      }
    }
    else if (parseState == ParseState::InsideLineComment)
    {
      if (code[i] == '\n')
      {
        parseState = ParseState::Normal;
        continue;
      }
      else if (i == code.length() - 1)
      {
        parseState = ParseState::Normal;
        continue;
      }
    }
    else if (parseState == ParseState::InsideBlockComment)
    {
      if (code[i] == '*' && QStringEx::peekNext(code, i) == '/')
      {
        parseState = ParseState::Normal;
        continue;
      }
    }
  }

  QStringList unnecessaryStuff;
  unnecessaryStuff << "";

  for (auto it = unnecessaryStuff.begin(); it != unnecessaryStuff.end(); it++)
  {
    while (code.contains(*it))
    {
      code.replace(*it, "");
    }
  }
}

void CppHelper::removeSvnId(QString& code)
{
  ParseState parseState = ParseState::Normal;

  int startIndex = 0;

  for (int i = 0; i < code.length(); ++i)
  {
    if (parseState == ParseState::Normal)
    {
      if (code[i] == '"' && QStringEx::peekPrevious(code, i) != '\\')
      {
        startIndex = i + 1;
        parseState = ParseState::InsideString;
        continue;
      }
      else if (code[i] == '/')
      {
        if (QStringEx::peekNext(code, i) == '/')
        {
          startIndex = i + 2;
          parseState = ParseState::InsideLineComment;
          ++i;
          continue;
        }
        else if (QStringEx::peekNext(code, i) == '*')
        {
          startIndex = i + 2;

          if (QStringEx::peekNextNonWhitespace(code, startIndex) == '$')
          {
            int startIndexSvnId = code.indexOf('$', startIndex);
            int endIndexSvnId = -1;

            if (startIndexSvnId > -1)
            {
              endIndexSvnId = code.indexOf('$', startIndexSvnId + 1);
            }

            if (startIndexSvnId > -1 && endIndexSvnId > -1)
            {
              code.remove(startIndexSvnId, endIndexSvnId - startIndexSvnId + 1);
            }
          }

          parseState = ParseState::InsideBlockComment;
          ++i;
          continue;
        }
      }
    }
    else if (parseState == ParseState::InsideString)
    {
      if (code[i] == '"' && QStringEx::peekPrevious(code, i) != '\\')
      {
        parseState = ParseState::Normal;
        continue;
      }
    }
    else if (parseState == ParseState::InsideLineComment)
    {
      if (code[i] == '\n')
      {
        parseState = ParseState::Normal;
        continue;
      }
      else if (i == code.length() - 1)
      {
        parseState = ParseState::Normal;
        continue;
      }
    }
    else if (parseState == ParseState::InsideBlockComment)
    {
      if (code[i] == '*' && QStringEx::peekNext(code, i) == '/')
      {
        parseState = ParseState::Normal;
        continue;
      }
    }
  }
}
