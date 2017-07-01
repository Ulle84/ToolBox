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
    void on_plainTextEditInput_textChanged();

  private:
    MainWindowUi* ui;
    QSettings* m_settings;
};

#endif // MAINWINDOW_H
