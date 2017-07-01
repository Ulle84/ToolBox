#ifndef MainWindow_h
#define MainWindow_h

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
    void on_pushButtonUIC_clicked();
    void on_pushButtonInputDirectory_clicked();
    void on_pushButtonOutputDirectory_clicked();
    void on_pushButtonRunUIC_clicked();
    void on_pushButtonRunResourceCompiler_clicked();
    void on_pushButtonResourceCompiler_clicked();

  private:
    Ui::MainWindow* ui;
    QSettings* m_settings;
};

#endif
