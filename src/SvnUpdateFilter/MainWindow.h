#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSettings;

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
    void on_plainTextEditInput_textChanged();

  private:
    Ui::MainWindow* ui;
    QSettings* m_settings;
};

#endif // MAINWINDOW_H
