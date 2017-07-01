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

    void sortLines();

  private slots:
    void on_plainTextEditSource_textChanged();

  private:


    QStringList m_textLines;

    MainWindowUi* ui;

    QSettings* m_settings;
};

#endif // MAINWINDOW_H
