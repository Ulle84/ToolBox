#ifndef TEMPLATA_H
#define TEMPLATE_H

#include <QDialog>

class TemplateUi;

class Template : public QDialog
{
    Q_OBJECT

  public:
    explicit Template(QWidget* parent = 0);
    ~Template();

  private:
    TemplateUi* ui;
};

#endif
