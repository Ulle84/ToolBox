// created on 2017-01-06 by Ulrich Belitz

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

class QSettings;

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(const QString& input, QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void on_pushButton_clicked();

  private:
    Ui::MainWindow* ui;

    QSettings* m_settings;
    QFile m_input;
};

#endif
