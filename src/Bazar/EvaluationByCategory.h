#ifndef EVALUATIONBYCATEGORY_H
#define EVALUATIONBYCATEGORY_H

#include <QWidget>

class ArticleManager;

class EvaluationByCategoryUi;

class EvaluationByCategory : public QWidget
{
  Q_OBJECT

public:
  explicit EvaluationByCategory(ArticleManager* articleManager, QWidget *parent = 0);
  ~EvaluationByCategory();

private slots:
  void on_pushButton_clicked();

  void on_lineEdit_returnPressed();

private:
  void doEvaluation();

  EvaluationByCategory Ui*ui;

  ArticleManager* m_articleManager;
};

#endif // EVALUATIONBYCATEGORY_H
