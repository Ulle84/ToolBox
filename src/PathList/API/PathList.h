// created on 2017-04-01 by Ulrich Belitz

#ifndef PATHLIST_H
#define PATHLIST_H

#include <QWidget>

#include "PathListAPI.h"

namespace Ui
{
  class PathList;
}

class PATHLIST_API PathList : public QWidget
{
    Q_OBJECT

  public:
    explicit PathList(QWidget* parent = 0);
    ~PathList();

	QStringList paths();
	QStringList directories();
	QStringList files();

	private slots:
	void on_pushButtonAddDirectory_clicked();
	void on_pushButtonAddFiles_clicked();
	void on_pushButtonClearList_clicked();

  private:
    Ui::PathList* ui;

	QString m_lastSelectedPath;
};

#endif
