#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QString>
#include <QIcon>

#include "CustomTypes.h"

class QSettings;
class QTimer;
class QSystemTrayIcon;
class QMenu;

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    enum State
    {
      Stopped,
      Running
    };

    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void update();
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();
    void on_pushButton4_clicked();
    void on_pushButton5_clicked();
    void on_pushButton6_clicked();
    void on_pushButton7_clicked();
    void on_pushButton8_clicked();
    void on_pushButton9_clicked();
    void on_pushButton10_clicked();
    void on_pushButton30_clicked();

  private:
    void startTimer(uint64 seconds);
    void startSitting();
    void startStanding();

    QString timeToString(int minutes, int seconds);

    Ui::MainWindow* ui;
    QSettings* m_settings;
    QTimer* m_timer;

    QDateTime m_dateTimeEnd;
    QIcon m_icon;

    State m_state;
};

#endif