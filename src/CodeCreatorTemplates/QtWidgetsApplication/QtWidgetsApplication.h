#ifndef QTWIDGETSAPPLICATION_H
#define QTWIDGETSAPPLICATION_H

#include <QWidget>

namespace Ui
{
  class QtWidgetsApplication;
}

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
