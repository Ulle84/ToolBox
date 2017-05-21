#ifndef QTWIDGETSAPPLICATION_H
#define QTWIDGETSAPPLICATION_H

#include <QWidget>

namespace Ui
{
  class ListEditTest;
}

class ListEditTest : public QWidget
{
    Q_OBJECT

  public:
    explicit ListEditTest(QWidget* parent = 0);
    ~ListEditTest();

  private:
    Ui::ListEditTest* ui;
};

#endif
