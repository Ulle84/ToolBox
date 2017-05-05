#ifndef QTWIDGETSAPPLICATION_H
#define QTWIDGETSAPPLICATION_H

#include <QWidget>

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


  private:
    Ui::DailyNotes* ui;
};

#endif
