#ifndef TIMERDONEDIALOG_H
#define TIMERDONEDIALOG_H

#include <QDialog>

class QSettings;

namespace Ui
{
  class TimerDoneDialog;
}

class TimerDoneDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit TimerDoneDialog(QWidget* parent = 0);
    ~TimerDoneDialog();

  private slots:
    void on_pushButtonClose_clicked();

  private:
    Ui::TimerDoneDialog* ui;
    QSettings* m_settings;
};

#endif
