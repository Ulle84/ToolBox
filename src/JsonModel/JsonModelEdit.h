#ifndef JSONMODELEDIT_H
#define JSONMODELEDIT_H

#include <QWidget>

class JsonModel;
class QAbstractItemView;

namespace Ui {
class JsonModelEdit;
}

class JsonModelEdit : public QWidget
{
  Q_OBJECT

public:
  explicit JsonModelEdit(QWidget *parent = 0);
  ~JsonModelEdit();

  void setModel(JsonModel* model);
  JsonModel* model();

  enum class ViewType
  {
    List,
    Table,
    Tree,
    Columns
  };

  void setViewType(ViewType viewType);

private:
  Ui::JsonModelEdit *ui;
  JsonModel* m_model = nullptr;
  QAbstractItemView* view = nullptr;
  QLayout* m_layout = nullptr;
};

#endif
