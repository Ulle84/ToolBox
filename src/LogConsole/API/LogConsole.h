// created on 2017-04-14 by Ulrich Belitz

#ifndef LOGCONSOLE_H
#define LOGCONSOLE_H

#include <QWidget>

#include "LogConsoleAPI.h"

class LogConsoleUi;

class LOGCONSOLE_API LogConsole : public QWidget
{
    Q_OBJECT

  public:
    explicit LogConsole(QWidget* parent = 0);
    ~LogConsole();

    void clear();
    void warning(const QString& text);
    void error(const QString& text);
    void success(const QString& text);
    void info(const QString& text);

  private:
    QString currentDateTime();

    Ui::LogConsole* ui;
};

#endif
