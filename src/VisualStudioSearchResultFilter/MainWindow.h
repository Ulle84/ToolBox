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

  private slots:
    void on_plainTextEditInput_textChanged();

    void on_lineEditBasePath_textEdited(const QString& arg1);

    void on_comboBox_currentIndexChanged(int index);

  private:
    void updateOutput();

    MainWindowUi* ui;

    QSettings* m_settings;
};

#endif // MAINWINDOW_H
