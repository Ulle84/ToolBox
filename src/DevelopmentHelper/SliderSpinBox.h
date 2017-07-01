#ifndef SLIDERSPINBOX_H
#define SLIDERSPINBOX_H

#include <QWidget>

class SliderSpinBoxUi;

class SliderSpinBox : public QWidget
{
    Q_OBJECT

  public:
    explicit SliderSpinBox(QWidget* parent = 0);
    ~SliderSpinBox();

    int value();
    void setValue(int value);

  public slots:
    void setMaximum(int maximum);
    void setMinimum(int minimum);
    void setText(QString text);

  signals:
    void valueChanged(int newValue);

  private:
    SliderSpinBoxUi* ui;
    int minimum;
    int maximum;
};

#endif // SLIDERSPINBOX_H
