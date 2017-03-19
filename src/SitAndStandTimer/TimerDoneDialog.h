#ifndef TimerDoneDialog_h
#define TimerDoneDialog_h

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
    enum NextPosition
    {
      Undefined,
      Standing,
      Sitting
    };

    explicit TimerDoneDialog(QWidget* parent = 0);
    ~TimerDoneDialog();

    NextPosition nextPosition();

  private slots:
    void on_pushButtonStartSitting_clicked();
    void on_pushButtonStartStanding_clicked();
    void on_pushButtonClose_clicked();

  private:
    Ui::TimerDoneDialog* ui;
    NextPosition m_nextPosition;
    QSettings* m_settings;
};

#endif
