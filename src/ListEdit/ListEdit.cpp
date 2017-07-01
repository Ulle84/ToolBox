#include <QStringListModel>
#include <QInputDialog>

#include "ListEdit.h"
#include "ListEditUi.h"

ListEdit::ListEdit(QWidget* parent) :
  QWidget(parent),
  ui(new ListEditUi)
{
  ui->setupUi(this);

  m_content << "a";
  m_content << "b";
  m_content << "c";
  m_content << "d";
  m_content << "abc";
  m_content << "ab";
  m_content << "abcd";
  
  m_model = new QStringListModel(this);  
  ui->listView->setModel(m_model);

  refreshContent();
}

ListEdit::~ListEdit()
{
  delete ui;
}

void ListEdit::on_pushButtonAdd_clicked()
{
  QString text = QInputDialog::getText(this, tr("enter text of new item"), tr("new item"));
  if (!text.isEmpty())
  {
    m_content.append(text);
    refreshContent();
    // TODO add to stringlist
  }
}

void ListEdit::refreshContent()
{
  m_model->setStringList(m_content);
}
