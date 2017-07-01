#ifndef QTWIDGETSAPPLICATION_H
#define QTWIDGETSAPPLICATION_H

#include <QWidget>
#include <QDate>

class DailyNotesUi;

class DailyNotes : public QWidget
{
    Q_OBJECT

  public:
    explicit DailyNotes(QWidget* parent = 0);
    ~DailyNotes();

  private slots:
    void on_codeEdit_textChanged();
    void on_calendarWidget_activated(const QDate& date);
    void on_calendarWidget_clicked(const QDate& date);
    void on_pushButtonOneDayBackward_clicked();
    void on_pushButtonToday_clicked();
    void on_pushButtonOneDayForward_clicked();
    void on_pushButtonOneMonthBackward_clicked();
    void on_pushButtonOneMonthForward_clicked();
    void on_pushButtonOneYearBackward_clicked();
    void on_pushButtonOneYearForward_clicked();


  private:
    void update(const QDate& date);
    QString path(const QDate& date);
    void saveCurrent();
    void setDate(const QDate& date);

    Ui::DailyNotes* ui;
    QDate m_selectedDate;
};

#endif
