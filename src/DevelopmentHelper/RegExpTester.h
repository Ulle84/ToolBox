#ifndef REGEXPTESTER_H
#define REGEXPTESTER_H

#include <QWidget>

class RegExpTesterUi;

class QSettings;

class RegExpTester : public QWidget
{
    Q_OBJECT

  public:
    explicit RegExpTester(QWidget* parent = 0);
    ~RegExpTester();

  private slots:
    void on_lineEditRegExp_textEdited(const QString& regExp);
    void on_lineEditTestString_textEdited(const QString& testString);

  private:
    void evaluate();

    RegExpTesterUi* ui;
    QSettings* m_settings;
};

#endif // REGEXPTESTER_H
