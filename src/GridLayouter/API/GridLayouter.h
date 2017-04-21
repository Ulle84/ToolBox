// created on 2017-04-15 by Ulrich Belitz

#ifndef GRIDLAYOUTER_H
#define GRIDLAYOUTER_H

#include <QWidget>

#include "GridLayouterAPI.h"

namespace Ui
{
  class GridLayouter;
}

// TODO declare designer widget as container for widgets - test preview

class GRIDLAYOUTER_API GridLayouter : public QWidget
{
    Q_OBJECT

  public:
    explicit GridLayouter(QWidget* parent = 0);
    ~GridLayouter();

	void addWidget(QWidget* widget);
	void rearrangeInGrid();

  private:
    Ui::GridLayouter* ui;
};

#endif
