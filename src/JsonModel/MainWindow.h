#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "JsonModel.h"

class MainWindowUi;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  void setTestContent(JsonModel* model);

  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
