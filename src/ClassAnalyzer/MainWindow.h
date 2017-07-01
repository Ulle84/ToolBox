#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "ClassAnalyzer.h"

class QSettings;

class MainWindowUi;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_pushButtonParseFolder_clicked();
  void on_pushButtonParseVernissage_clicked();

private:
  void updateResult();

  Ui::MainWindow *ui;

  ClassAnalyzer m_classAnalyzer;
  QSettings* m_settings;
  QString m_lastSelectedDirectory;
};

#endif
