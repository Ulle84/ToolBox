#ifndef NUMBERDISPLAY_H
#define NUMBERDISPLAY_H

#include <QWidget>

class NumberDisplayUi;

class QTimer;

class NumberDisplay : public QWidget
{
    Q_OBJECT

  public:
    explicit NumberDisplay(QWidget* parent = 0);
    ~NumberDisplay();

  public slots:
    void setNewGeneratedNumber(int newNumber);

    private slots:
    void update();

  private:
    NumberDisplayUi* ui;

    QTimer* m_timer;
    int m_currentNumber;
};

#endif
