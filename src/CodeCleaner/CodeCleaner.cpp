#include <iostream>

#include <QDebug>
#include <QStringList>
#include <QVector>

#include "QStringEx.h"
#include "QConverter.h"
#include "File.h"

#include "CodeCleaner.h"

// TODO look for performance issues - replace for complete string might be expensive!!!

CodeCleaner::CodeCleaner()
{
}

void CodeCleaner::process(QString& code, CodeType codeType)
{
  m_codeType = codeType;

  m_commentHandler.parseAndReplaceComments(code, m_options.m_cleanComments);

  m_stringHandler.parseAndReplaceStrings(code);

  if (m_options.m_removeUnnecessaryStuff)
  {
    removeUnnecessaryStuff(code);
  }

  if (m_options.m_removeDoubleEmptyLines)
  {
    removeDoubleEmptyLines(code);
  }

  if (m_options.m_removeEmptyLinesBeforeClosingBracket)
  {
    removeEmptyLinesBeforeClosingBracket(code);
  }

  if (m_options.m_removeEmptyLinesAfterOpeningBracket)
  {
    removeEmptyLinesAfterOpeningBracket(code);
  }

  if (m_options.m_removeLineBreaksInsideParentheses)
  {
    removeLineBreaksInsideParentheses(code);
  }

  if (m_options.m_removeUnnecessarySpaces)
  {
    removeUnnecessarySpaces(code);
  }

  if (m_options.m_cleanElementInitializiers)
  {
    cleanElementInitializiers(code);
  }

  if (m_options.m_addMPrefixToMembers)
  {
    addMPrefixToMembers(code);
  }

  if (m_options.m_beautify)
  {
    beautify(code);
  }

  m_commentHandler.revertComments(code);
  m_stringHandler.revertStrings(code);

  if (m_options.m_doBlockCodeFormatting)
  {
    m_blockCodeFormatter.process(code);
  }
}

void CodeCleaner::removeDoubleEmptyLines(QString& code)
{
  while (code.contains("\n\n\n"))
  {
    code.replace("\n\n\n", "\n\n");
  }
}

void CodeCleaner::removeEmptyLinesBeforeClosingBracket(QString& code)
{
  // TODO improve performance by better implementation
  for (unsigned int indent = 0; indent < 20; indent++)
  {
    QString space = createSpaceString(indent * 2);
    QString search = "\n\n" + space + "}";
    QString replace = "\n" + space + "}";
    code.replace(search, replace);
  }
}

void CodeCleaner::removeLineBreaksInsideParentheses(QString& code)
{
  // parse sign by sign - if inside parentheses -> eliminate \n
  // attention - only delete '\n' if no comment occurred

  int nParentheses = 0;
  bool lastSignWasSlash = false;
  bool commentOccurred = false;

  for (int i = 0; i < code.length(); ++i)
  {
    if (code[i] == '/')
    {
      if (lastSignWasSlash)
      {
        commentOccurred = true;
      }
      else
      {
        lastSignWasSlash = true;
      }
    }
    else
    {
      lastSignWasSlash = false;

      if (code[i] == '(' && !QStringEx::isSurrounded(code, i, '\''))
      {
        nParentheses++;
      }
      else if (code[i] == ')' && !QStringEx::isSurrounded(code, i, '\''))
      {
        nParentheses--;
      }
      else if (code[i] == '\n')
      {
        if (nParentheses > 0 && !commentOccurred)
        {
          if (QStringEx::peekPrevious(code, i) != '\\')
          {
            code.remove(i, 1);
            i--;
          }
        }
      }

      if (nParentheses == 0)
      {
        commentOccurred = false;
      }
    }
  }
}

void CodeCleaner::removeEmptyLinesAfterOpeningBracket(QString& code)
{
  // TODO better performance possible?
  code.replace("{\n\n", "{\n");
}

void CodeCleaner::removeUnnecessaryStuff(QString& code)
{
  QStringList unnecessaryStuff;
  unnecessaryStuff << "QT_NAMESPACE::";

  for (auto it = unnecessaryStuff.begin(); it != unnecessaryStuff.end(); it++)
  {
    while (code.contains(*it))
    {
      code.replace(*it, "");
    }
  }

  QString searchText = "{ ; }";

  if (m_codeType == CodeType::Declaration)
  {
    code.replace(searchText, "{}");
  }
  else if (m_codeType == CodeType::Implementation)
  {
    code.replace(searchText, "{\n}");
  }
}

void CodeCleaner::cleanElementInitializiers(QString& code)
{
  // TODO the following implementation does wrong things in this case:

  /*
    test::test() // comment
    : a(true) // trailing comment
    // or bock comment
    , b(false)
  */

  // --> comments need special handling in this case!

  /*if (m_codeType == Source)
  {
    code.replace("\n    : ", " :\n    ");
    code.replace("\n    , ", ",\n    ");
  }*/

  // idea for correct implementation:
  // check if line starts with sign ',' (same procedure applies on sign ':')
  // remove ',' in current line
  // goto last closing parenthesis and attach sign here
}

void CodeCleaner::addMPrefixToMembers(QString& code)
{
  QMap<QString, QString> replaceMap;
  //#] = #
  replaceMap[" _" ] = " m_";
  replaceMap["\n_"] = "\nm_";
  replaceMap["(_" ] = "(m_";
  replaceMap["._" ] = ".m_";
  replaceMap["->_"] = "->m_";
  replaceMap["!_" ] = "!m_";
  replaceMap["&_" ] = "&m_";
  replaceMap["*_" ] = "*m_";
  replaceMap[")_" ] = ")m_";
  replaceMap[">_" ] = ">m_";
  QStringList codeLines = code.split("\n");

  for (auto codeLine = codeLines.begin(); codeLine != codeLines.end(); ++codeLine)
  {
    if (!codeLine->trimmed().startsWith('#') && !codeLine->trimmed().startsWith("typedef"))
    {
      for (auto it = replaceMap.begin(); it != replaceMap.end(); it++)
      {
        codeLine->replace(it.key(), it.value());
      }
    }
  }

  code = codeLines.join("\n");
}

void CodeCleaner::beautify(QString& code)
{
  // TODO is there a better implementation?
  if (m_codeType == CodeType::Implementation)
  {
    code.replace("\n  {}", "\n  {\n  }");
    code.replace("\n    {}", "\n    {\n    }");
  }
  else if (m_codeType == CodeType::Declaration)
  {
    code.replace("\n  {}", " {}");
    code.replace("\n    {}", " {}");
  }
}

QString CodeCleaner::createSpaceString(unsigned int length)
{
  return createString(" ", length);
}

QString CodeCleaner::createString(QString characters, unsigned int length)
{
  QString string;

  for (uint i = 0; i < length; i++)
  {
    string.append(characters);
  }

  return string;
}

bool CodeCleaner::indexValid(int index)
{
  return index > -1;
}

void CodeCleaner::setOptions(const Options& options)
{
  m_options = options;
}

void CodeCleaner::removeUnnecessarySpaces(QString& code)
{
  // TODO improve performance by better implementation
  // go through code sign by sign - only once - do all whitespace stuff in one run
  // see
  // * removeDoubleEmptyLines
  // * removeEmptyLinesAfterOpeningBracket
  // * removeEmptyLinesBeforeClosingBracket
  QStringList stringList = QConverter::toStringList(code);

  for (auto& it : stringList)
  {
    uint16 nLeadingSpaces = QStringEx::removeLeadingSpaces(it);

    while (it.contains("  "))
    {
      it.replace("  ", " ");
    }

    it.replace(". ", ".");
    it.replace(" ,", ",");

    if (nLeadingSpaces > 0)
    {
      QStringEx::addLeadingSpaces(it, nLeadingSpaces);
    }
  }

  code = QConverter::toString(stringList);
}
