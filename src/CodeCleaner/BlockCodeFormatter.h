#ifndef BLOCKCODEFORMATTER_H
#define BLOCKCODEFORMATTER_H

#include <QString>

typedef unsigned int uint;

class BlockCodeFormatter
{
  public:
    BlockCodeFormatter();
    void process(QString& code);

  private:
    enum ParseState
    {
      undefined,
      normal,
      insideBlock,
      insideDoubleQuote,
      insideSingleQuote
    };

    void formatBlock(QStringList& input, uint start, uint end);
    void testBlockFormatting();
    void simplify(QString& string);

    QString m_startTag;
    QString m_seperator;
};

#endif // BLOCKCODEFORMATTER_H
