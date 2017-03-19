// created on 2017-03-15 by Ulrich Belitz

#ifndef SIMPLEHTMLEDIT_H
#define SIMPLEHTMLEDIT_H

#include <QWidget>

#include "SimpleHtmlEditAPI.h"

namespace Ui
{
  class SimpleHtmlEdit;
}

class SIMPLEHTMLEDIT_API SimpleHtmlEdit : public QWidget
{
    Q_OBJECT

  public:
    explicit SimpleHtmlEdit(QWidget* parent = 0);
    ~SimpleHtmlEdit();

    void setText(const QString& text);
    QString text();

    void setSplitterState(const QByteArray& state);
    QByteArray splitterState();

  private slots:
    void on_codeEditSimpleHtml_textChanged();

  private:
    Ui::SimpleHtmlEdit* ui;
};

#endif
