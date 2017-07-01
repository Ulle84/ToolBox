#ifndef QTDESIGNERWIDGET_H
#define QTDESIGNERWIDGET_H

#include <QWidget>

class QtDesignerWidgetUi;

class QtDesignerWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit QtDesignerWidget(QWidget* parent = 0);
    ~QtDesignerWidget();

  private:
    QtDesignerWidgetUi* ui;
};

#endif
