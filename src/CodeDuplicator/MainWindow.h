#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "CustomTypes.h"

class QSettings;

class MainWindowUi;

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void on_pushButtonDuplicate_clicked();
    void onPathChanged(const QString& path);

  private:
    bool process(const QString& source, const QString& destination, const QString& sourceName, const QString& destinationName, uint offsetIndex);
    void changeFilePath(QString& filePath, const QString& newFileName);

    MainWindowUi* ui;

    QSettings* m_settings;
};

#endif
