// created on 2017-04-15 by Ulrich Belitz

#include <QLayout>
#include <QLayoutItem>

#include "GridLayouter.h"
#include "ui_GridLayouter.h"

GridLayouter::GridLayouter(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::GridLayouter)
{
  ui->setupUi(this);
}

GridLayouter::~GridLayouter()
{
  delete ui;
}

void GridLayouter::addWidget(QWidget* widget)
{
	ui->verticalLayout->addWidget(widget);
}

void GridLayouter::rearrangeInGrid()
{
	// iterate over all widgets in vertical layout
	int nWidgets = ui->verticalLayout->count();
	for (int i = 0; i < nWidgets; ++i)
	{
		QLayoutItem* layoutItem = ui->verticalLayout->itemAt(i);
		if (layoutItem)
		{
			QLayout* layout = layoutItem->widget()->layout();
			if (layout)
			{
				int nWidgets2 = layout->count();
				for (int j = 0; j < nWidgets2; ++j)
				{
					ui->gridLayout->addWidget(layout->takeAt(0)->widget(), i, j);
					//QLayoutItem* layoutItem = ;

				}
			}
		}


	}
}
