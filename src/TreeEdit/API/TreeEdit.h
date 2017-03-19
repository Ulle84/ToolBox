// created on 2017-03-06 by Ulrich Belitz

#ifndef TREEEDIT_H
#define TREEEDIT_H

#include <QWidget>
#include <QItemSelection>

#include "TreeEditAPI.h"

// TODO store state of collapsed
// TODO activate/deactivate actions depending on selected tree-item
// TODO disable search filter before moving
// TODO provide context menu or key-bindings which only are triggered, if treeEdit has focus

class QAction;

class TreeModel;
class ProxyModel;

namespace Ui
{
  class TreeEdit;
}

class TREEEDIT_API TreeEdit : public QWidget
{
    Q_OBJECT

  public:
    explicit TreeEdit(QWidget* parent = 0);
    ~TreeEdit();

    QByteArray headerState() const;
    void setHeaderState(const QByteArray& headerState);

    void setMaxIndentation(unsigned int maxIndentation);
    void setTree(const QJsonObject& tree);
    QJsonObject toJson();

  //protected:
  //  void keyPressEvent(QKeyEvent* e) override;

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

  signals:
    void idChanged(int id);
    void itemRemoved(int id);

  protected:
    void contextMenuEvent(QContextMenuEvent* event) override;

  private slots:
    void on_lineEditSearch_textChanged(const QString& searchText);
    void onTreeViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void onResetRequired(int id);

  private:
    void setupActions();
    void selectId(int id);
    QModelIndex modelIndex(int id, const QModelIndex& parent);
    void getAllIds(QMap<int, QModelIndex>& ids, QModelIndex parent);
    void setupModel(const QJsonObject& tree);
    QModelIndex selectedIndex();
    int indentation(const QModelIndex& modelIndex);

    QAction* m_actionAddNode;
    QAction* m_actionAddChildNode;
    QAction* m_actionRemoveNode;
    QAction* m_actionInsertColumn;
    QAction* m_actionRemoveColumn;

    QAction* m_actionMoveDown;
    QAction* m_actionMoveUp;
    QAction* m_actionMoveLeft;
    QAction* m_actionMoveRight;

    Ui::TreeEdit* ui;

    TreeModel* m_treeModel;
    ProxyModel* m_proxyModel;

    int m_lastSelectedId = 0;

    unsigned int m_maxIndentation = std::numeric_limits<unsigned int>::max();
};

#endif
