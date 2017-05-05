#ifndef SIMPLEHTMLCONVERTER_H
#define SIMPLEHTMLCONVERTER_H

#include <QString>

#include "Attribute.h"
#include "SharedAPI.h"

class SHARED_API SimpleHtmlConverter
{
  public:
    SimpleHtmlConverter();

    QString toHtml(const QString& simpleHtml);

  private:
    QString removeComments(const QString& simpleHtml);
    //QString indent(int indentationLevel);
    QString parseTag(const QString& simpleHtml, int position);
    Attribute parseAttribute(const QString& simpleHtml, int& position);
    //QString endTag(const QString& startTag);

    const int m_indent = 2;
    const QString m_beginComment = "(((";
    const QString m_endComment = ")))";
};

#endif // CONVERTER_H