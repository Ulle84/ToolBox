#include <QStringList>
#include <QDebug>

#include "SmlConverter.h"
#include "SharedResources.h"
#include "QStringEx.h"
#include "Converter.h"

SmlConverter::SmlConverter()
{
}

QString SmlConverter::toHtml(const QString& sml, bool createInfrastructure)
{
  QString input = removeComments(sml);

  processLists(input);

  // TODO post processing for lists & tables

  QString result;

  if (createInfrastructure)
  {
    result.append("<html>\n<head>\n<style>");
    result.append(SharedResources::defaultStyleSheet());
    result.append("\n</style>\n</head>\n<body>\n");
  }

  QList<QString> tags;

  QChar c;
  bool lastCharWasOpeningBracket = false;
  //bool insideSol = false;
  //int startIndexSol = 0;

  for (int i = 0; i < input.size(); ++i)
  {
    c = input[i];

    if (c == '(')
    {
      if (lastCharWasOpeningBracket)
      {
        Attribute attribute = parseAttribute(input, i);

        if (attribute.isValid())
        {
          result.insert(result.length() - 1, QString(" %1=\"%2\"").arg(attribute.name()).arg(attribute.value()));
        }
        else
        {
          tags.append(QString());
        }
      }
      else
      {
        QString tag = parseTag(input, i);

        tags.append(tag);

        if (!tag.isEmpty())
        {
          result.remove(result.length() - tag.length(), tag.length());

          //if (tag == "sol")
          //{
          //  startIndexSol = i + 1;
          //  insideSol = true;
          //  //result.append("<ol>");
          //}
          //else
          {
            result.append(QString("<%1>").arg(tag));
          }
        }
      }
    }
    else if (c == ')')
    {
      if (!tags.empty())
      {
        QString tag = tags.last();
        tags.removeLast();

        if (!tag.isEmpty())
        {
          if (lastCharWasOpeningBracket)
          {
            result.insert(result.length() - 1, '/');
          }
          else
          {
            //if (tag == "sol")
            //{
            //  insideSol = false;
            //  result.append(sol(input, startIndexSol, i - startIndexSol));
            //  //result.append("</ol>");
            //}
            //else
            {
              result.append(QString("</%1>").arg(tag));
            }
          }
        }
      }
    }
    else
    {
      //if (!insideSol)
      {
        result.append(c);
      }
    }

    lastCharWasOpeningBracket = (c == '(');
  }

  if (createInfrastructure)
  {
    result.append("\n</body>\n</html>");
  }

  return result;
}

QString SmlConverter::removeComments(const QString& simpleHtml)
{
  // TODO nested comments?
  // this part here might be easy, but what about the code-highlighting?

  QString string = simpleHtml;

  int beginIndex = string.indexOf(m_beginComment);
  int endIndex = -1;

  while (beginIndex >= 0)
  {
    endIndex = string.indexOf(m_endComment, beginIndex + m_beginComment.length());

    if (endIndex >= 0)
    {
      string.remove(beginIndex, endIndex - beginIndex + m_endComment.length());
    }

    beginIndex = string.indexOf(m_beginComment, beginIndex + 1);
  }

  return string;
}

/*QString SmlConverter::indent(int indentationLevel)
{
  return QString(indentationLevel * m_indent, ' ');
}*/

QString SmlConverter::parseTag(const QString& simpleHtml, int position)
{
  if (position <= 0)
  {
    return QString();
  }

  int originalPosition = position;

  QChar c;

  bool runLoop = true;

  while (runLoop)
  {
    c = simpleHtml[--position];

    if (c == ' ' || c == '(' || c == ')' || c == '\n' || c == '\t')
    {
      ++position;
      runLoop = false;
    }

    if (position == 0)
    {
      runLoop = false;
    }
  }

  return simpleHtml.mid(position, originalPosition - position);
}

Attribute SmlConverter::parseAttribute(const QString& simpleHtml, int& position)
{
  int originalPosition = position;

  QChar c;

  bool runLoop = true;

  while (runLoop)
  {
    c = simpleHtml[++position];

    if (c == ')')
    {
      runLoop = false;
    }

    if (position == simpleHtml.size() - 1)
    {
      // reached end of string to early
      position = originalPosition;
      return Attribute();
    }
  }

  QString attribute = simpleHtml.mid(originalPosition + 1, position - originalPosition - 1);

  QStringList tokens = attribute.split('=');

  if (tokens.size() != 2)
  {
    position = originalPosition;
    return Attribute();
  }

  QString name = tokens[0].trimmed();
  QString value = tokens[1].trimmed();

  if (name.isEmpty() || value.isEmpty())
  {
    position = originalPosition;
    return Attribute();
  }

  return Attribute(name, value);
}

QString SmlConverter::sol(const QString& input, int startPosition, int length)
{
  // TODO first spacds

  QString result;

  QStringList stringList = Converter::toStringList(input.mid(startPosition, length));

  int lastLeadingSpaces = 0;

  for (auto it = stringList.begin(); it != stringList.end(); ++it)
  {
    QString line = *it;

    int nLeadingSpaces = QStringEx::nLeadingSpaces(line);

    if (nLeadingSpaces > lastLeadingSpaces)
    {
      result.append(QString(nLeadingSpaces, ' '));
      result.append("<ol>\n");
    }

    if (!line.isEmpty())
    {
      line.insert(nLeadingSpaces, "<li>");
      line.append("</li>\n");

      result.append(line);
    }

    if (nLeadingSpaces < lastLeadingSpaces)
    {
      result.append(QString(nLeadingSpaces, ' '));
      result.append("</ol>\n");
    }

    lastLeadingSpaces = nLeadingSpaces;
  }

  // TODO
  return result;
}

int SmlConverter::indexOfMatchingClosingParenthesis(const QString& sml, int startIndex)
{
  int nOpenedParenthesis = 1;

  for (int i = startIndex; i < sml.length(); ++i)
  {
    if (sml[i] == '(')
    {
      ++nOpenedParenthesis;
    }
    else if (sml[i] == ')')
    {
      --nOpenedParenthesis;
    }

    if (nOpenedParenthesis == 0)
    {
      return i;
    }
  }

  return -1;
}

void SmlConverter::processLists(QString& sml)
{
  QStringList searchStrings;
  searchStrings << "sol(\n";
  searchStrings << "sul(\n";

  for (auto it = searchStrings.begin(); it != searchStrings.end(); ++it)
  {
    int startIndex = sml.indexOf(*it);
    int endIndex = -1;

    while (startIndex > -1)
    {
      endIndex = indexOfMatchingClosingParenthesis(sml, startIndex + it->length());

      if (endIndex > -1)
      {
        sml.replace(startIndex, endIndex - startIndex + 1, processList(Converter::toStringList(sml.mid(startIndex, endIndex - startIndex + 1))));
      }

      startIndex = sml.indexOf(*it);
    }
  }  
}

QString SmlConverter::processList(const QStringList& list)
{
  QString result;

  int lastLeadingSpaces = -1;

  for (auto it = list.begin(); it != list.end(); ++it)
  {
    if (it == list.begin())
    {
      result.append(it->mid(1)); // cut off first character 's'
    }
    else
    {
      result.append('\n');

      QString line = *it;
      if (line.trimmed() == ")")
      {
        result.append(line);
        continue;
      }


      

      

      int nLeadingSpaces = QStringEx::nLeadingSpaces(line);

      if (lastLeadingSpaces > 0)
      {
        if (nLeadingSpaces > lastLeadingSpaces)
        {
          result.append(QString("%1ol(\n").arg(QString(nLeadingSpaces - 2, ' ')));
        }
        else if (nLeadingSpaces < lastLeadingSpaces)
        {
          result.append(QString("%1)\n").arg(QString(nLeadingSpaces, ' ')));
        }
      }

      
      
        line.insert(nLeadingSpaces, "li(");
        line.append(")");

        result.append(line);
           

      lastLeadingSpaces = nLeadingSpaces;
    }
  }

  return result;
}

/*QString SmlConverter::endTag(const QString &startTag)
{
  if (startTag.isEmpty())
  {
    return startTag;
  }

  QString string = startTag;

  string.insert(startTag.length() - 2, '/');
  return string;
}*/
