#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class QSettings;

#include "CMakeHelper.h"

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void on_pushButtonSearch_clicked();

  private:
    Ui::MainWindow* ui;
    CMakeHelper m_cMakeHelper;
    QSettings* m_settings;
};

#endif // MAINWINDOW_H