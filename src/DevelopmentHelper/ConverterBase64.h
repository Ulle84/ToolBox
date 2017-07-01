#ifndef CONVERTERBASE64_H
#define CONVERTERBASE64_H

#include <QWidget>

class ConverterBase64Ui;

class ConverterBase64 : public QWidget
{
    Q_OBJECT

  public:
    explicit ConverterBase64(QWidget* parent = 0);
    ~ConverterBase64();

  private slots:
    void on_lineEditPlainText_editingFinished();
    void on_lineEditBase64EncodedText_editingFinished();

  private:
    ConverterBase64Ui* ui;
};

#endif // CONVERTERBASE64_H
