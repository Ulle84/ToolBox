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

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(PathType pathType READ pathType WRITE setPathType)
    Q_PROPERTY(QString labelText READ labelText WRITE setLabelText)
    Q_PROPERTY(QString buttonText READ buttonText WRITE setButtonText)

  public:
    explicit PathSelector(QWidget* parent = 0);
    ~PathSelector();

    QString path();
    void setPath(const QString& path);

    enum class PathType
    {
      Directory,
      File
    };
    Q_ENUM(PathType)

    PathType pathType() const;
    void setPathType(PathType pathType);

    QString labelText() const;
    void setLabelText(const QString& text);

    QString buttonText() const;
    void setButtonText(const QString& text);

    void clearHistory(int leftItems = 0);

  signals:
    void pathChanged(const QString& path);

  private slots:
    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged(const QString& text);

  private:
    Ui::PathSelector* ui;
    PathType m_pathType = PathType::Directory;
};

#endif
