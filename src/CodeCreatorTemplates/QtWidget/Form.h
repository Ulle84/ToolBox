#ifndef FORM_H
#define FORM_H

#include <QWidget>

class FormUi;

class Form : public QWidget
{
    Q_OBJECT

  public:
    explicit Form(QWidget* parent = 0);
    ~Form();

  private:
    FormUi* ui;
};

#endif
