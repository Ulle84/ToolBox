#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindowUi;

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void on_plainTextEdit_textChanged();

    void on_pushButton_clicked();

  private:
    MainWindowUi* ui;
};

#endif // MAINWINDOW_H
