// created on 2017-01-23 by Ulrich Belitz

#include "CppHelper.h"

CppHelper::CppHelper()
{
}

CppHelper::~CppHelper()
{
}

void CppHelper::process(QString& code)
{
  ParseState parseState = ParseState::Normal;

  int startIndex = 0;

  for (int i = 0; i < code.length(); ++i)
  {
    if (parseState == ParseState::Normal)
    {
      if (code[i] == '"' && peekPrevious(code, i) != '\\')
      {
        startIndex = i + 1;
        parseState = ParseState::InsideString;
        continue;
      }
      else if (code[i] == '/')
      {
        if (peekNext(code, i) == '/')
        {
          startIndex = i + 2;
          parseState = ParseState::InsideLineComment;
          i++;
          continue;
        }
        else if (peekNext(code, i) == '*')
        {
          startIndex = i + 2;
          parseState = ParseState::InsideBlockComment;
          i++;
          continue;
        }
      }
      // TODO sanitize code if possible
    }
    else if (parseState == ParseState::InsideString)
    {
      if (code[i] == '"' && peekPrevious(code, i) != '\\')
      {
        m_strings.append(code.mid(startIndex, i - startIndex));
        code.remove(startIndex, i - startIndex);
        parseState = ParseState::Normal;
        continue;
      }
    }
    else if (parseState == ParseState::InsideLineComment)
    {
      // TODO check if content of line comment is necessary
      if (code[i] == '\n')
      {
        m_lineComments.append(code.mid(startIndex, i - startIndex));
        code.remove(startIndex, i - startIndex);
        parseState = ParseState::Normal;
        continue;
      }
      else if (i == code.length() - 1)
      {
        m_lineComments.append(code.mid(startIndex, i - startIndex + 1));
        code.remove(startIndex, i - startIndex + 1);
        parseState = ParseState::Normal;
        continue;
      }
    }
    else if (parseState == ParseState::InsideBlockComment)
    {
      // TODO check if content of block comment is neseccary
      if (code[i] == '*' && peekNext(code, i) == '/')
      {
        m_blockComments.append(code.mid(startIndex, i - startIndex));
        code.remove(startIndex, i - startIndex);
        parseState = ParseState::Normal;
        i++;
        continue;
      }
    }
  }
}

void CppHelper::revert(QString& code)
{
}

QChar CppHelper::peekPrevious(const QString& code, int index)
{
  if (index <= 0)
  {
    return QChar('\0');
  }

  return code[index - 1];
}

QChar CppHelper::peekNext(const QString& code, int index)
{
  if (index >= code.length())
  {
    return QChar('\0');
  }

  return code[index + 1];
}

QString CppHelper::parseNextWord(const QString& code, int& index)
{
  // TODO implement this functionality
  return QString();
}

QString CppHelper::parsePreviousWord(const QString& code, int& index)
{
  // TODO implement this functionality
  return QString();
}
