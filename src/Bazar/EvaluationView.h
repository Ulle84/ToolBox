#ifndef EVALUATIONVIEW_H
#define EVALUATIONVIEW_H

#include <QWidget>

class QByteArray;

class EvaluationViewUi;

class EvaluationView : public QWidget
{
  Q_OBJECT

public:
  explicit EvaluationView(const QString& name, QWidget *parent = 0);
  ~EvaluationView();
  void setName(const QString& name);
  QString getName();
  void setHtmlContent(QString htmlContent);

private slots:
  void on_webView_loadFinished(bool loadFinished);
  void on_pushButton_clicked();

private:
  Ui::EvaluationView *ui;
  QString m_name;
};

#endif // EVALUATIONVIEW_H
