// created on 2017-03-25 by Ulrich Belitz

#include <QFileDialog>

#include "PathSelector.h"
#include "PathSelectorUi.h"

PathSelector::PathSelector(QWidget* parent) :
  QWidget(parent),
  ui(new PathSelectorUi)
{
  ui->setupUi(this);
}

PathSelector::~PathSelector()
{
  delete ui;
}

void PathSelector::setPath(const QString &path)
{
  ui->comboBox->setCurrentText(path);
  ui->comboBox->insertItem(0, ui->comboBox->currentText());
  emit pathChanged(path);
}

QString PathSelector::path()
{
  return ui->comboBox->currentText();
}

void PathSelector::setPathType(PathSelector::PathType pathType)
{
  m_pathType = pathType;
}

void PathSelector::setLabelText(const QString &text)
{
  ui->label->setText(text);
}

QString PathSelector::labelText() const
{
  return ui->label->text();
}

QString PathSelector::buttonText() const
{
  return ui->pushButton->text();
}

PathSelector::PathType PathSelector::pathType() const
{
  return m_pathType;
}

void PathSelector::setButtonText(const QString &text)
{
  ui->pushButton->setText(text);
}

void PathSelector::clearHistory(int leftItems)
{
  while (ui->comboBox->count() > leftItems)
  {
    ui->comboBox->removeItem(leftItems);
  }
}

/*void PathSelector::on_lineEdit_textChanged(const QString& path)
{
  QFile file(path);
  //ui->lineEdit->setProperty("input", (path.isEmpty() || file.exists() ? "correct" : "wrong"));

  // unfortunately this is neccessary, after changing dynamic properties
  //qApp->setStyleSheet(qApp->styleSheet());
}*/

void PathSelector::on_pushButton_clicked()
{
  QString path;

  if (m_pathType == PathType::File)
  {
    path = QFileDialog::getOpenFileName(this, tr("select file"), ui->comboBox->currentText());
  }
  else if (m_pathType == PathType::Directory)
  {
    path = QFileDialog::getExistingDirectory(this, tr("select directory"), ui->comboBox->currentText());
  }

  if (!path.isEmpty())
  {
    setPath(path);
  }
}

void PathSelector::on_comboBox_currentIndexChanged(const QString& text)
{
	emit pathChanged(text);
}
