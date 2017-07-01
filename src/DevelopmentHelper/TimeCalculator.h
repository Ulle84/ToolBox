#ifndef TIMECALCULATOR_H
#define TIMECALCULATOR_H

#include <QWidget>

class TimeCalculatorUi;

class TimeCalculator : public QWidget
{
    Q_OBJECT

  public:
    explicit TimeCalculator(QWidget* parent = 0);
    ~TimeCalculator();

  private slots:
    void on_lineEditNanoseconds_editingFinished();

    void on_lineEditMiroseconds_editingFinished();

    void on_lineEditMilliseconds_editingFinished();

    void on_lineEditSeconds_editingFinished();

    void on_lineEditMinutes_editingFinished();

    void on_lineEditHours_editingFinished();

    void on_lineEditDays_editingFinished();

    void on_lineEditYears_editingFinished();

    void changeTime(double newTimeInNanoseconds);



  private:
    TimeCalculatorUi* ui;
    double timeInNanoseconds;
};

#endif // TIMECALCULATOR_H
