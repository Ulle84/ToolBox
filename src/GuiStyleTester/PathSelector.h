#ifndef PATHSELECTOR_H
#define PATHSELECTOR_H

#include <QWidget>
#include <QString>

class PathSelectorUi;

class PathSelector : public QWidget
{
    Q_OBJECT

  public:
    explicit PathSelector(QWidget* parent = 0);
    ~PathSelector();

    void setPath(const QString& path);
    QString path();

  private slots:
    void on_lineEdit_textChanged(const QString& path);
    void on_pushButton_clicked();

  private:
    PathSelectorUi* ui;
};

#endif