// created on 2017-03-25 by Ulrich Belitz

#ifndef PATHSELECTOR_H
#define PATHSELECTOR_H

// TODO order items in combobox by last usage - latest should be on top - not possible?
// TODO save state
// TODO load state
// TODO set background color of lineEdit to red, if path does not exist

/* Idea
   instead of combobox:
   line edit + push-button which opens dialog with searchable and editable history - much more flexible than edit-box
*/

/* Idea
   PathEditor with autocompletion (parses file system)
   every part of the path (every directory) is clickable so directory jumps are easy
*/

#include <QWidget>
#include <QString>

#include "PathSelectorAPI.h"

namespace Ui
{
  class PathSelector;
}

class PATHSELECTOR_API PathSelector : public QWidget
{
    Q_OBJECT

  public:
    explicit PathSelector(QWidget* parent = 0);
    ~PathSelector();

  void setPath(const QString& path);
  QString path();

  enum class PathType
  {
    Directory,
    File
  };
  void setPathType(PathType pathType);

  void setLabelText(const QString& text);
  void setButtonText(const QString& text);

  void clearHistory(int leftItems = 0);

signals:
  void pathChanged(const QString& path);

private slots:
  void on_pushButton_clicked();

private:
  Ui::PathSelector *ui;
  PathType m_pathType = PathType::Directory;
};

#endif
