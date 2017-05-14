#ifndef SMLCONVERTER_H
#define SMLCONVERTER_H

#include <QString>

#include "Attribute.h"
#include "SharedAPI.h"

class SmlConverter
{
  public:
    SmlConverter();

    QString toHtml(const QString& sml, bool createInfrastructure = true);

  private:
    QString removeComments(const QString& simpleHtml);
    //QString indent(int indentationLevel);
    QString parseTag(const QString& simpleHtml, int position);
    Attribute parseAttribute(const QString& simpleHtml, int& position);
    //QString endTag(const QString& startTag);
    QString sol(const QString& input, int startPosition, int length);

    int indexOfMatchingClosingParenthesis(const QString& sml, int startIndex);

    void processLists(QString& sml);
    QString processList(const QStringList& list);

    const int m_indent = 2;
    const QString m_beginComment = "(((";
    const QString m_endComment = ")))";
};

#endif
