// created on 2017-01-12 by Ulrich Belitz

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButtonAdd_clicked();
    void on_pushButtonDelete_clicked();
    void on_lineEditDirectory_returnPressed();
    void on_comboBoxTestCase_currentIndexChanged(const QString& text);

  private:
    Ui::MainWindow* ui;

    QSettings* m_settings;
    const QString m_inputFileNameEnd = "_input.txt";
    const QString m_outputFileNameEnd = "_output.txt";
};

#endif
