#ifndef PRIZECORRECTION_H
#define PRIZECORRECTION_H

#include <QDialog>

class PrizeCorrectionUi;

class PrizeCorrection : public QDialog
{
  Q_OBJECT

public:
  explicit PrizeCorrection(QWidget *parent = 0);
  ~PrizeCorrection();
  void setPrize(double prize);
  double getPrize();

private slots:
  void on_pushButtonOK_clicked();
  void on_pushButtonCancel_clicked();

private:
  PrizeCorrection Ui*ui;
};

#endif // PRIZECORRECTION_H
