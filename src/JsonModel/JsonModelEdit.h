#ifndef JSONMODELEDIT_H
#define JSONMODELEDIT_H

#include <QWidget>

class JsonModel;
class QAbstractItemView;
class QAction;
class ProxyModel;

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

      void setMaxIndentation(unsigned int maxIndentation);

signals:
  //void idChanged(int id);
  void itemRemoved(int id);

public slots:
    bool addNode();
    bool addChildNode();
    bool removeNode();
    bool insertColumn();
    bool removeColumn();

    bool moveDown();
    bool moveUp();
    bool moveLeft();
    bool moveRight();



protected:
  void contextMenuEvent(QContextMenuEvent* event) override;

private:
  void setupActions();
  int indentation(const QModelIndex& modelIndex);

  Ui::JsonModelEdit *ui;
  JsonModel* m_model = nullptr;
  QAbstractItemView* view = nullptr;
  QLayout* m_layout = nullptr;

      ProxyModel* m_proxyModel = nullptr;

  QAction* m_actionAddNode;
      QAction* m_actionAddChildNode;
      QAction* m_actionRemoveNode;
      QAction* m_actionInsertColumn;
      QAction* m_actionRemoveColumn;

      QAction* m_actionMoveDown;
      QAction* m_actionMoveUp;
      QAction* m_actionMoveLeft;
      QAction* m_actionMoveRight;

          unsigned int m_maxIndentation = std::numeric_limits<unsigned int>::max();
};

#endif
