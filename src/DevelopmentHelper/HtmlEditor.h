#ifndef HTMLEDITOR_H
#define HTMLEDITOR_H

#include <QWidget>

class HtmlEditorUi;

class HtmlEditor : public QWidget
{
    Q_OBJECT

  public:
    explicit HtmlEditor(QWidget* parent = 0);
    ~HtmlEditor();

  private slots:
    void on_pushButton_clicked();

  private:
    Ui::HtmlEditor* ui;
};

#endif // HTMLEDITOR_H
