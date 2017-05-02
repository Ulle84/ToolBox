#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui
{
  class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

  public:
    explicit Widget(QWidget* parent = 0);
    ~Widget();

  public slots:
  void setNewParameter(const QString& name, const QString& value);
  void setNewGeneratedNumber(int newNumber);

  signals:
    void parameterChanged(const QString& name, const QString& value);

    private slots:
    void on_pushButton_clicked();

  private:
    Ui::Widget* ui;
};

#endif