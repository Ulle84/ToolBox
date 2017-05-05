#ifndef QTWIDGETSAPPLICATION_H
#define QTWIDGETSAPPLICATION_H

#include <QWidget>
#include <QDate>

namespace Ui
{
  class DailyNotes;
}

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

  private:
    void update(const QDate& date);
    QString path(const QDate& date);
    void saveCurrent();

    Ui::DailyNotes* ui;
    QDate m_selectedDate;
};

#endif
