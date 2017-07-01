#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "AutoHotKeyHelper.h"

class QSettings;

class MainWindowUi;

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void on_pushButtonSelectFile_clicked();
    void on_pushButtonAppendToFile_clicked();
    void on_lineEditFile_textChanged(const QString& text);
    void on_lineEditKey_textChanged(const QString& text);

  private:
    Ui::MainWindow* ui;
    QSettings* m_settings;
    AutoHotKeyHelper m_autoHotKeyHelper;
};

#endif // MAINWINDOW_H