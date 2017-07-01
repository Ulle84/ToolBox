#ifndef QTWIDGETSAPPLICATION_H
#define QTWIDGETSAPPLICATION_H

#include <QWidget>

class QtWidgetsApplicationUi;

class QtWidgetsApplication : public QWidget
{
    Q_OBJECT

  public:
    explicit QtWidgetsApplication(QWidget* parent = 0);
    ~QtWidgetsApplication();

  private:
    Ui::QtWidgetsApplication* ui;
};

#endif
