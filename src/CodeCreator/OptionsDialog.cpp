#include <QSettings>

#include "OptionsDialog.h"
#include "OptionsDialogUi.h"

OptionsDialog::OptionsDialog(QSettings* settings, QWidget* parent) :
  m_settings(settings),
  QDialog(parent),
  ui(new Ui::OptionsDialog)
{
  ui->setupUi(this);

  if (m_settings)
  {
    ui->lineEditAuthor->setText(m_settings->value("author").toString());
    ui->checkBoxCreateAuthorComment->setChecked(m_settings->value("createAuthorComment").toBool());
    ui->checkBoxIncludeDate->setChecked(m_settings->value("includeDate").toBool());
  }
}

OptionsDialog::~OptionsDialog()
{
  if (m_settings)
  {
    m_settings->setValue("author", ui->lineEditAuthor->text());
    m_settings->setValue("createAuthorComment", ui->checkBoxCreateAuthorComment->isChecked());
    m_settings->setValue("includeDate", ui->checkBoxIncludeDate->isChecked());
  }

  delete ui;
}
