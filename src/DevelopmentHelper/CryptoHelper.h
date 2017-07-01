#ifndef CRYPTOHELPER_H
#define CRYPTOHELPER_H

#include <QWidget>

class CryptoHelperUi;

class CryptoHelper : public QWidget
{
    Q_OBJECT

  public:
    explicit CryptoHelper(QWidget* parent = 0);
    ~CryptoHelper();

  private slots:
    void on_lineEditInput_returnPressed();
    void on_pushButton_clicked();

  private:
    CryptoHelperUi* ui;
};

#endif // CRYPTOHELPER_H
