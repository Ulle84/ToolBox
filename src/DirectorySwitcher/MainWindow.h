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

    void setWorkingDirectory(const QString& workingDirectory);

  private slots:
    void on_pushButtonSelectDirectory_clicked();
    void on_pushButtonCheckDirectory_clicked();
    void on_listWidgetProjects_currentTextChanged(const QString& currentText);
    void on_pushButtonSaveInformation_clicked();
    void on_pushButtonSaveSettings_clicked();
    void on_pushButtonSwitch_clicked();
    void on_pushButtonCreateNew_clicked();

  private:
    void checkDirectory();
    void updateInfo();
    void updateSettings();
    void showUserMessage(QString message);

    MainWindowUi* ui;
    QSettings* m_settings;
    QString m_currentInfoFile;
    QString m_currentSettingsFile;
    QString m_infoFileName;
    QString m_settingsFileName;
};

#endif // MAINWINDOW_H
