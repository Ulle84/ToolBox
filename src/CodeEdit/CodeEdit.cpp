// created on 2017-02-23 by Ulrich Belitz

#include <QFont>
#include <QDebug>
#include <QKeyEvent>
#include <QDebug>

#include "CodeEdit.h"

#include "XmlHighlighter.h"
#include "SmlHighlighter.h"
#include "CppHighlighter.h"
#include "QFontEx.h"
#include "QStringEx.h"

CodeEdit::CodeEdit(QWidget* parent) :
  QTextEdit(parent)
{
  setFont(QFontEx::monospace());
  connect(this, &CodeEdit::cursorPositionChanged, this, &CodeEdit::onCursorPositionChanged);
}

void CodeEdit::keyPressEvent(QKeyEvent* e)
{
  // TOOD refactor: split this method!

  // Ctrl Combinations
  if (e->modifiers() & Qt::ControlModifier)
  {
    if (e->key() == Qt::Key_D)
    {
      QTextCursor cursor = textCursor();

      QString currentLine = cursor.block().text();

      cursor.insertText("\n");
      cursor.insertText(currentLine);

      setTextCursor(cursor);
      return;
    }
    else if (e->key() == Qt::Key_R)
    {
      QTextCursor cursor = textCursor();

      cursor.select(QTextCursor::BlockUnderCursor);
      cursor.removeSelectedText();

      setTextCursor(cursor);
    }
  }

  if (e->key() == Qt::Key_Tab)
  {
    QTextCursor cursor = textCursor();
    cursor.insertText("  ");
    setTextCursor(cursor);
    return;
  }

  if (e->key() == Qt::Key_Return)
  {
    QTextCursor cursor = textCursor();

    QString currentLine = cursor.block().text();
    QString leadingSpaces = QStringEx::leadingSpaces(currentLine);

    cursor.insertText("\n");
    cursor.insertText(leadingSpaces);

    if (QStringEx::startsWith(currentLine, "li(", true))
    {
      cursor.insertText("li()");
      cursor.movePosition(QTextCursor::PreviousCharacter);
    }

    setTextCursor(cursor);
    return;
  }

  QString string;

  if (e->key() == Qt::Key_Apostrophe)
  {
    string = "\'\'";
  }
  else if (e->key() == Qt::Key_QuoteDbl)
  {
    string = "\"\"";
  }
  else if (e->key() == Qt::Key_ParenLeft)
  {
    string = "()";
  }
  else if (e->key() == Qt::Key_BracketLeft)
  {
    string = "[]";
  }
  else if (e->key() == Qt::Key_BraceLeft)
  {
    string = "{}";
  }

  if (string.isEmpty())
  {
    QTextEdit::keyPressEvent(e);
  }
  else
  {
    QTextCursor cursor = textCursor();
    cursor.insertText(string);
    cursor.movePosition(QTextCursor::PreviousCharacter);
    setTextCursor(cursor);
  }
}

void CodeEdit::setCodeHighlightingType(CodeHighlightingType codeHighlightingType)
{
  if (m_syntaxHighlighter)
  {
    delete m_syntaxHighlighter;
  }

  switch (codeHighlightingType)
  {
    case CodeHighlightingType::Cpp:
      m_syntaxHighlighter = new CppHighlighter(document());
      break;

    case CodeHighlightingType::Sml:
      m_syntaxHighlighter = new SmlHighlighter(document());
      break;

    case CodeHighlightingType::Xml:
      m_syntaxHighlighter = new XmlHighlighter(document());
      break;
  }
}

void CodeEdit::onCursorPositionChanged()
{
  QTextCursor cursor = textCursor();

  if (cursor.position() < 0 || cursor.position() >= toPlainText().length())
  {
    setExtraSelections(QList<QTextEdit::ExtraSelection>());
    return;
  }

  if (toPlainText().at(cursor.position()) == '(')
  {
    int index = indexOfMatchingClosingParenthesis(toPlainText(), cursor.position());

    if (index == -1)
    {
      highlightIndices(QList<int>() << cursor.position(), HighlightingType::MismachtingParenthesis);
    }
    else
    {
      highlightIndices(QList<int>() << cursor.position() << index, HighlightingType::MachtingParenthesis);
    }
  }
  else if (toPlainText().at(cursor.position()) == ')')
  {
    int index = indexOfMatchingOpeningParenthesis(toPlainText(), cursor.position());

    if (index == -1)
    {
      highlightIndices(QList<int>() << cursor.position(), HighlightingType::MismachtingParenthesis);
    }
    else
    {
      highlightIndices(QList<int>() << cursor.position() << index, HighlightingType::MachtingParenthesis);
    }
  }
  else
  {
    setExtraSelections(QList<QTextEdit::ExtraSelection>());
  }
}

int CodeEdit::indexOfMatchingClosingParenthesis(const QString& code, int index)
{
  int nOpenendParenthesis = 1;

  for (int i = index + 1; i < code.length(); ++i)
  {
    if (code[i] == ')')
    {
      nOpenendParenthesis--;
    }
    else if (code[i] == '(')
    {
      nOpenendParenthesis++;
    }

    if (nOpenendParenthesis == 0)
    {
      return i;
    }
  }

  return -1;
}

int CodeEdit::indexOfMatchingOpeningParenthesis(const QString& code, int index)
{
  int nClosedParenthesis = 1;

  for (int i = index - 1; i >= 0; --i)
  {
    if (code[i] == ')')
    {
      nClosedParenthesis++;
    }
    else if (code[i] == '(')
    {
      nClosedParenthesis--;
    }

    if (nClosedParenthesis == 0)
    {
      return i;
    }
  }

  return -1;
}

void CodeEdit::highlightIndices(QList<int> indices, CodeEdit::HighlightingType highlightingType)
{
  QList<QTextEdit::ExtraSelection> selections;

  QTextEdit::ExtraSelection selection;
  QTextCharFormat format = selection.format;

  if (highlightingType == HighlightingType::MachtingParenthesis)
  {
    format.setBackground(Qt::green);
  }
  else if (highlightingType == HighlightingType::MismachtingParenthesis)
  {
    format.setBackground(Qt::red);
  }

  selection.format = format;

  QTextCursor cursor = textCursor();

  for (auto it = indices.begin(); it != indices.end(); ++it)
  {
    cursor.setPosition(*it);
    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    selection.cursor = cursor;
    selections.append(selection);
  }

  setExtraSelections(selections);
}
