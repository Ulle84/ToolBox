#ifndef CONVERTER_H
#define CONVERTER_H

#include <QWidget>

class ConverterUi;

class Converter : public QWidget
{
    Q_OBJECT

  public:
    explicit Converter(QWidget* parent = 0);
    ~Converter();

  private:
    Ui::Converter* ui;
};

#endif // CONVERTER_H
