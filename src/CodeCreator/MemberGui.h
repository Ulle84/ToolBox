#ifndef MEMBERGUI_H
#define MEMBERGUI_H

#include <QWidget>
#include <QString>

#include "Member.h"

class MemberGuiUi;

class MemberGui : public QWidget
{
    Q_OBJECT

  public:
    explicit MemberGui(QWidget* parent = 0);
    ~MemberGui();

    Member member() const;
    void setMember(const Member& member);

  private:
    MemberGuiUi* ui;
};

#endif // MEMBERGUI_H
