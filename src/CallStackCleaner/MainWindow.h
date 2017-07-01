// created on 2017-01-04 by Ulrich Belitz

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSettings;

class MainWindowUi;

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void on_pushButtonCleanCallStack_clicked();

  private:
    MainWindowUi* ui;

    QSettings* m_settings;
    const int m_messageShowTimeMilliSeconds = 2000;
};

#endif
