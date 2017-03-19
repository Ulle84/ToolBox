#ifndef QTDESIGNERWIDGET_H
#define QTDESIGNERWIDGET_H

#include <QWidget>

namespace Ui
{
  class QtDesignerWidget;
}

class QtDesignerWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit QtDesignerWidget(QWidget* parent = 0);
    ~QtDesignerWidget();

  private:
    Ui::QtDesignerWidget* ui;
};

#endif
