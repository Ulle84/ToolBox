#ifndef TEXTCONVERTER_H
#define TEXTCONVERTER_H

#include <QWidget>

class TextConverterUi;

class TextConverter : public QWidget
{
    Q_OBJECT

  public:
    explicit TextConverter(QWidget* parent = 0);
    ~TextConverter();

  private:
    TextConverterUi* ui;
};

#endif // TEXTCONVERTER_H
