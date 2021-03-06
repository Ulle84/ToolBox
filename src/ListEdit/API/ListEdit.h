#ifndef LISTEDIT_H
#define LISTEDIT_H

#include <QWidget>
#include <QStringList>

#include "ListEditAPI.h"

class QStringListModel;

class ListEditUi;

class LISTEDIT_API ListEdit : public QWidget
{
    Q_OBJECT

  public:
    explicit ListEdit(QWidget* parent = 0);
    ~ListEdit();

    private slots:
    void on_pushButtonAdd_clicked();

  private:
    void refreshContent();

    ListEditUi* ui;

    QStringList m_content;
    QStringListModel* m_model;
};

#endif
