#ifndef ITERATEOVERCONTAINER_H
#define ITERATEOVERCONTAINER_H

#include <QWidget>

class IterateOverContainerUi;

class IterateOverContainer : public QWidget
{
    Q_OBJECT

  public:
    explicit IterateOverContainer(QWidget* parent = 0);
    ~IterateOverContainer();

  private slots:
    void on_lineEditContainerName_returnPressed();
    void on_lineEditIteratorName_returnPressed();

  private:
    void createCode();

    IterateOverContainerUi* ui;
};

#endif // ITERATEOVERCONTAINER_H
