#include <QStringList>
#include <QList>
#include <QPair>
#include <QDebug>

#include "BlockCodeFormatter.h"
BlockCodeFormatter::BlockCodeFormatter() :
  m_startTag("//#"),
  m_seperator("#")
{
}

void BlockCodeFormatter::process(QString& code)
{
  QStringList lines = code.split('\n');

  QList<QPair<uint, uint>> blocks;

  ParseState parseState = normal;
  uint lineNumber = 0;
  uint blockStart = 0;

  for (auto it = lines.begin(); it != lines.end(); ++it)
  {
    QString codeLine = it->trimmed();

    if (parseState == normal)
    {
      if (codeLine.startsWith(m_startTag))
      {
        blockStart = lineNumber;
        parseState = insideBlock;
      }
    }
    else if (parseState == insideBlock)
    {
      if (codeLine.isEmpty() || codeLine.startsWith(m_startTag) || codeLine.startsWith('}') || codeLine.startsWith('{'))
      {
        blocks.append(qMakePair(blockStart, lineNumber - 1));

        if (codeLine.startsWith(m_startTag))
        {
          blockStart = lineNumber;
        }
        else
        {
          parseState = normal;
        }
      }
    }

    lineNumber++;
  }

  for (auto it = blocks.begin(); it != blocks.end(); ++it)
  {
    formatBlock(lines, it->first, it->second);
  }

  code = lines.join('\n');
}

void BlockCodeFormatter::formatBlock(QStringList& input, uint start, uint end)
{
  if (input.length() < 3)
  {
    return;
  }

  QString instructions = input[start];
  QString leadingWhitespace = instructions.left(instructions.indexOf(m_startTag));

  instructions = instructions.trimmed();

  QStringList symbols = instructions.mid(m_startTag.length()).split(m_seperator, QString::SkipEmptyParts);

  for (uint i = start + 1; i <= end; i++)
  {
    simplify(input[i]);
  }

  int startPosition = 0;

  for (auto symbol = symbols.begin(); symbol != symbols.end(); ++symbol)
  {
    QMap<uint /*inputLine*/, uint /*positionOfSymbol*/> positions;

    // parse position of symbol
    for (uint i = start + 1; i <= end; ++i)
    {
      positions[i] = input[i].indexOf(*symbol, startPosition);
    }

    // find out maximum
    uint maximum = 0;

    for (auto it = positions.begin(); it != positions.end(); ++it)
    {
      if (it.value() > maximum)
      {
        maximum = it.value();
      }
    }

    startPosition = maximum + 1;

    // fill up with spaces
    for (uint i = start + 1; i <= end; ++i)
    {
      if (positions[i] < maximum)
      {
        QString fillString((maximum - positions[i]), ' ');
        input[i] = input[i].insert(positions[i], fillString);
      }
    }
  }

  for (uint i = start + 1; i <= end; i++)
  {
    input[i] = input[i].prepend(leadingWhitespace);
  }
}

void BlockCodeFormatter::simplify(QString& string)
{
  string = string.trimmed();

  ParseState parseState = normal;

  for (int i = 0; i < string.length(); i++)
  {
    QChar currentChar = string[i];

    if (parseState == normal)
    {
      if (currentChar == '\"')
      {
        if (i == 0)
        {
          parseState = insideDoubleQuote;
        }
        else
        {
          if (string[i - 1] != '\\')
          {
            parseState = insideDoubleQuote;
          }
        }
      }
      else if (currentChar == '\'')
      {
        if (i == 0)
        {
          parseState = insideSingleQuote;
        }
        else
        {
          if (string[i - 1] != '\\')
          {
            parseState = insideSingleQuote;
          }
        }
      }
      else if (currentChar == '\t' || currentChar == '\v' || currentChar == '\f' || currentChar == '\r' || currentChar == ' ')
      {
        if (i != 0)
        {
          if (string[i - 1] == ' ')
          {
            string.remove(i--, 1);
          }
          else
          {
            string[i] = ' ';
          }
        }
      }
    }
    else if (parseState == insideDoubleQuote)
    {
      if (currentChar == '\"' && string[i - 1] != '\\')
      {
        parseState = normal;
      }
    }
    else if (parseState == insideSingleQuote)
    {
      if (currentChar == '\'' && string[i - 1] != '\\')
      {
        parseState = normal;
      }
    }
  }
}

void BlockCodeFormatter::testBlockFormatting()
{
  //# # = #
  int     horst                 = 0;
  bool    hans                  = false;
  double  aVeryLongVariableName = 999.0;
  QString aString               = "string    with    a lot   of spaces";

  //# # = #
  double firstValue  = 0.999;
  double secondValue = 123.45;
}
