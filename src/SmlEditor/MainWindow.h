// created on 2017-02-23 by Ulrich Belitz

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>

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
    void onTreeEditIdChanged(int id);
    void onTreeEditItemRemoved(int id);

  private:
    void writeFile();

    void setContent(const QJsonArray& json);
    QJsonArray contentToJson();

    int m_currentId = -1;
    QMap<int, QString> m_textContent;

    Ui::MainWindow* ui;

    QSettings* m_settings;
};

#endif
