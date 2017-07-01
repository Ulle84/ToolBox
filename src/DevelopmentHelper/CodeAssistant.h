#ifndef CODEASSISTANT_H
#define CODEASSISTANT_H

#include <QWidget>

class CodeAssistantUi;

class CodeAssistant : public QWidget
{
    Q_OBJECT

  public:
    explicit CodeAssistant(QWidget* parent = 0);
    ~CodeAssistant();

  private:
    Ui::CodeAssistant* ui;
};

#endif // CODEASSISTANT_H
