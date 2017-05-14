#ifndef QTWIDGETDLL_H
#define QTWIDGETDLL_H

#include <QWidget>

#include "QtWidgetDllAPI.h"

namespace Ui
{
  class QtWidgetDll;
}

class QTWIDGETDLL_API QtWidgetDll : public QWidget
{
    Q_OBJECT

  public:
    explicit QtWidgetDll(QWidget* parent = 0);
    ~QtWidgetDll();

  private:
    Ui::QtWidgetDll* ui;
};

#endif