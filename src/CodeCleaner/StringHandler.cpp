#include "StringHandler.h"

StringHandler::StringHandler()
{
}

void StringHandler::parseAndReplaceStrings(QString& code)
{
  m_strings.clear();

  int startIndex = nextTokenIndex(code, 0);
  int endIndex = 0;

  while (isIndexValid(startIndex))
  {
    endIndex = nextTokenIndex(code, startIndex + 1);

    if (isIndexValid(endIndex))
    {
      int length = endIndex - startIndex + 1;
      m_strings.append(code.mid(startIndex, length));
      code.replace(startIndex, length, m_replacementMask.arg(m_strings.length() - 1));
      endIndex = nextTokenIndex(code, startIndex + 1);
    }
    else
    {
      break;
    }

    startIndex = nextTokenIndex(code, endIndex + 1);
  }
}

void StringHandler::revertStrings(QString& code)
{
  int numberOfStrings = 0;

  for (auto it = m_strings.begin(); it != m_strings.end(); ++it)
  {
    code.replace(m_replacementMask.arg(numberOfStrings++), *it);
  }
}

int StringHandler::nextTokenIndex(const QString& code, int startIndex)
{
  int index = 0;
  bool searchToken = true;

  while (searchToken)
  {
    index = code.indexOf(m_token, startIndex);

    if (index < 1)
    {
      searchToken = false;
    }
    else
    {
      if (code[index - 1] == '\\')
      {
        startIndex = index + 1;
      }
      else
      {
        searchToken = false;
      }
    }
  }

  return index;
}

bool StringHandler::isIndexValid(int index)
{
  return index > -1;
}
