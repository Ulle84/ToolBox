#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSettings;
class LogViewer;
class ProxyModel;

class MainWindowUi;

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void on_lineEdit_textChanged(const QString& text);
	void on_pathSelector_pathChanged(const QString& path);

  private:
    MainWindowUi* ui;

    LogViewer* m_logViewer = nullptr;
    ProxyModel* m_proxyModel = nullptr;

    QSettings* m_settings;
};

#endif // MAINWINDOW_H