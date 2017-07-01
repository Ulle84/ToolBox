#ifndef ARTICLERETURN_H
#define ARTICLERETURN_H

#include <QDialog>

class ArticleReturnUi;

class ArticleReturn : public QDialog
{
    Q_OBJECT

public:
    explicit ArticleReturn(QWidget *parent = 0);
    ~ArticleReturn();

  int getSellerNumber();
  int getArticleNumber();

private slots:
  void on_buttonBox_accepted();

private:
    ArticleReturn Ui*ui;

    int m_sellerNumber;
    int m_articleNumber;
};

#endif // ARTICLERETURN_H
