#ifndef QTWIDGETSAPPLICATION_H
#define QTWIDGETSAPPLICATION_H

#include <QWidget>

namespace Ui
{
  class NumberEditTest;
}

class NumberEditTest : public QWidget
{
    Q_OBJECT

  public:
    explicit NumberEditTest(QWidget* parent = 0);
    ~NumberEditTest();

    private slots:
    void on_pushButton_clicked();

  private:
    Ui::NumberEditTest* ui;
};

#endif
