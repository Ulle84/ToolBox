// created on 2017-02-23 by Ulrich Belitz

#ifndef CODEEDIT_H
#define CODEEDIT_H

#include <QTextEdit>

#include "CodeEditAPI.h"

class QSyntaxHighlighter;

class CODEEDIT_API CodeEdit : public QTextEdit
{
    Q_OBJECT

  public:
    explicit CodeEdit(QWidget* parent = 0);

    enum class CodeHighlightingType
    {
      Cpp,
      Sml,
      Xml
    };
    void setCodeHighlightingType(CodeHighlightingType codeHighlightingType);

  protected:
    virtual void keyPressEvent(QKeyEvent* e) override;

  private slots:
    void onCursorPositionChanged();

  private:
    int indexOfMatchingClosingParenthesis(const QString& code, int index);
    int indexOfMatchingOpeningParenthesis(const QString& code, int index);

    enum class HighlightingType
    {
      MachtingParenthesis,
      MismachtingParenthesis
    };

    void highlightIndices(QList<int> indices, HighlightingType highlightingType);

    QSyntaxHighlighter* m_syntaxHighlighter = nullptr;
};

#endif
