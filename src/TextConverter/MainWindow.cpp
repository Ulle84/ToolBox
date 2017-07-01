#include <QClipboard>

#include "MainWindow.h"
#include "MainWindowUi.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new MainWindowUi)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_plainTextEdit_textChanged()
{
  QString input = ui->plainTextEdit->toPlainText();
  input.replace("\n", "\\n");
  input.replace("\t", "\\t");
  ui->lineEdit->setText(QString("\"%1\"").arg(input));
}

void MainWindow::on_pushButton_clicked()
{
  QApplication::clipboard()->setText(ui->lineEdit->text());
}
