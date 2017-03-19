#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QString>
#include <QIcon>

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
    enum CurrentPosition
    {
      Undefined,
      Standing,
      Sitting
    };

    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void update();
    void on_pushButtonStartSitting_clicked();
    void on_pushButtonStartStanding_clicked();

  private:
    void startSitting();
    void startStanding();

    QString timeToString(int minutes, int seconds);

    Ui::MainWindow* ui;
    QSettings* m_settings;
    QTimer* m_timer;

    CurrentPosition m_state;

    QDateTime m_dateTimeEnd;
    QIcon m_icon;
};

#endif // MAINWINDOW_H