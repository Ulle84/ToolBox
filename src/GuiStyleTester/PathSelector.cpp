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

void PathSelector::setPath(const QString& path)
{
  ui->lineEdit->setText(path);
}

QString PathSelector::path()
{
  return ui->lineEdit->text();
}

void PathSelector::on_lineEdit_textChanged(const QString& path)
{
  QFile file(path);
  //ui->lineEdit->setStyleSheet(QString("background-color: %1").arg((path.isEmpty() || file.exists()) ? "white" : "red"));
  ui->lineEdit->setProperty("input", (path.isEmpty() || file.exists() ? "correct" : "wrong"));

  // unfortunately this is neccessary, after changing dynamic properties
  qApp->setStyleSheet(qApp->styleSheet());
}

void PathSelector::on_pushButton_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("select file"), ui->lineEdit->text());

  if (!fileName.isEmpty())
  {
    ui->lineEdit->setText(fileName);
  }
}