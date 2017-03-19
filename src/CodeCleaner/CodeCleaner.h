#ifndef CODECLEANER_H
#define CODECLEANER_H

#include <QChar>
#include <QString>

#include "CommentHandler.h"

#include "Options.h"
#include "StringHandler.h"
#include "BlockCodeFormatter.h"

class CodeCleaner
{
  public:
    enum class CodeType
    {
      Undefined,
      Declaration,
      Implementation,
      DeclarationWithImplementations
    };

    CodeCleaner();

    void process(QString& code, CodeType codeType);
    void setOptions(const Options& options);

  private:
    void addMPrefixToMembers(QString& code);
    void beautify(QString& code);
    void cleanElementInitializiers(QString& code);
    void removeDoubleEmptyLines(QString& code);
    void removeEmptyLinesAfterOpeningBracket(QString& code);
    void removeEmptyLinesBeforeClosingBracket(QString& code);
    void removeLineBreaksInsideParentheses(QString& code);

    void removeUnnecessarySpaces(QString& code);
    void removeUnnecessaryStuff(QString& code);

    QString createSpaceString(unsigned int length);
    QString createString(QString characters, unsigned int length);

    bool indexValid(int index);

    Options m_options;
    CommentHandler m_commentHandler;
    StringHandler m_stringHandler;
    BlockCodeFormatter m_blockCodeFormatter;
    CodeType m_codeType;
};

#endif
