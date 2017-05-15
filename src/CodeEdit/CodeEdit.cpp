// created on 2017-02-23 by Ulrich Belitz

#include <QFont>
#include <QDebug>
#include <QKeyEvent>
#include <QDebug>

#include "CodeEdit.h"

#include "XmlHighlighter.h"
#include "SmlHighlighter.h"
#include "CppHighlighter.h"
#include "Font.h"
#include "QStringEx.h"

CodeEdit::CodeEdit(QWidget* parent) :
  QTextEdit(parent)
{
  setFont(Font::monospace());
  connect(this, &CodeEdit::cursorPositionChanged, this, &CodeEdit::onCursorPositionChanged);
}

void CodeEdit::keyPressEvent(QKeyEvent* e)
{
  if (e->key() != Qt::Key_Tab
      && e->key() != Qt::Key_Backtab
      && e->key() != Qt::Key_Return)
  {
    QTextEdit::keyPressEvent(e);
  }

  QTextCursor cursor = textCursor();

  if (e->modifiers() & Qt::ControlModifier)
  {
    if (e->key() == Qt::Key_D)
    {
      QString currentLine = cursor.block().text();

      cursor.insertText("\n");
      cursor.insertText(currentLine);
    }
    else if (e->key() == Qt::Key_R)
    {
      cursor.select(QTextCursor::BlockUnderCursor);
      cursor.removeSelectedText();
    }
  }

  if (e->key() == Qt::Key_Tab)
  {
    cursor.insertText(QString(2 - cursor.columnNumber() % 2, ' '));
  }
  else if (e->key() == Qt::Key_Backtab)
  {
    if (QStringEx::isInsideLeadingSpace(cursor.block().text(), cursor.columnNumber()))
    {
      cursor.deletePreviousChar();

      if (cursor.columnNumber() % 2 == 1)
      {
        cursor.deletePreviousChar();
      }
    }
    else
    {
      cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor, 2 - cursor.columnNumber() % 2);
    }
  }
  else if (e->key() == Qt::Key_Return)
  {
    QString currentLine = cursor.block().text();
    QString leadingSpaces = QStringEx::leadingSpaces(currentLine);

    cursor.insertText("\n");
    cursor.insertText(leadingSpaces);

    // TODO do this always if ( is before cursor and ) is after cursor
    if (currentLine.endsWith("sul()"))
    {
      int n = QStringEx::nLeadingSpaces(currentLine);
      cursor.insertText(QString(n + 2, ' '));
      cursor.insertText("\n");
      cursor.movePosition(QTextCursor::PreviousCharacter);
    }
      //qDebug() << "dköfjas";

    if (QStringEx::startsWith(currentLine, "li(", true))
    {
      cursor.insertText("li()");
      cursor.movePosition(QTextCursor::PreviousCharacter);
    }
  }
  else if (e->key() == Qt::Key_Apostrophe)
  {
    cursor.insertText("\'");
    cursor.movePosition(QTextCursor::PreviousCharacter);
  }
  else if (e->key() == Qt::Key_QuoteDbl)
  {
    cursor.insertText("\"");
    cursor.movePosition(QTextCursor::PreviousCharacter);
  }
  else if (e->key() == Qt::Key_ParenLeft)
  {
    cursor.insertText(")");
    cursor.movePosition(QTextCursor::PreviousCharacter);
  }
  else if (e->key() == Qt::Key_BracketLeft)
  {
    cursor.insertText("]");
    cursor.movePosition(QTextCursor::PreviousCharacter);
  }
  else if (e->key() == Qt::Key_BraceLeft)
  {
    cursor.insertText("}");
    cursor.movePosition(QTextCursor::PreviousCharacter);
  }

  setTextCursor(cursor);
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
