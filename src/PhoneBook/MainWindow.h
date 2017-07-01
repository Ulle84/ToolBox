#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSettings;
class PhoneBook;
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

  private:
    MainWindowUi* ui;

    PhoneBook* m_phoneBook;
    ProxyModel* m_proxyModel;

    QSettings* m_settings;
};

#endif // MAINWINDOW_H