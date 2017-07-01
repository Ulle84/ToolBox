// created on 2017-02-23 by Ulrich Belitz

#ifndef CASECHANGER_H
#define CASECHANGER_H

#include <QWidget>

class CaseChangerUi;

class CaseChanger : public QWidget
{
    Q_OBJECT

  public:
    explicit CaseChanger(QWidget* parent = 0);
    ~CaseChanger();

  private slots:
    void on_pushButtonUppercase_clicked();
    void on_pushButtonLowercase_clicked();

  private:
    Ui::CaseChanger* ui;
};

#endif
