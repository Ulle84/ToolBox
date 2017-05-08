// created on 2017-03-15 by Ulrich Belitz

#ifndef SMLEDIT_H
#define SMLEDIT_H

#include <QWidget>

#include "SmlEditAPI.h"

namespace Ui
{
  class SmlEdit;
}

class SMLEDIT_API SmlEdit : public QWidget
{
    Q_OBJECT

  public:
    explicit SmlEdit(QWidget* parent = 0);
    ~SmlEdit();

    void setText(const QString& text);
    QString text();

    void setSplitterState(const QByteArray& state);
    QByteArray splitterState();

  private slots:
    void on_codeEditSimpleHtml_textChanged();

  private:
    Ui::SmlEdit* ui;
};

#endif
