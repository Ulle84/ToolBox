#ifndef QTWIDGETSAPPLICATION_H
#define QTWIDGETSAPPLICATION_H

#include <QWidget>

class ListEditTestUi;

class ListEditTest : public QWidget
{
    Q_OBJECT

  public:
    explicit ListEditTest(QWidget* parent = 0);
    ~ListEditTest();

  private:
    ListEditTestUi* ui;
};

#endif
