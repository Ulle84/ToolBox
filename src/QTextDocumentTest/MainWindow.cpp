#include <QTextDocument>
#include <QTextCursor>
#include <QTextList>
#include <QTextTable>
#include <QTextTableFormat>
#include <QFileDialog>
#include <QFileInfo>
#include <QPrinter>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QTextDocument* textDocument = ui->textEdit->document();
  QTextCursor textCursor = ui->textEdit->textCursor();
  //textCursor.insertHtml("<ul><li>one  blub</li><li>two</li></ul>");
  //textCursor.insertHtml("<table style=\"border: 1 px solid black\"><tr><td>one blub</td><td>two</td></tr><tr><td>one</td><td>two</td></tr></table>");

  //ui->textEdit->setTextCursor(textCursor);
  //return;



  textCursor.insertText("horst");
  ui->textEdit->setTextCursor(textCursor);

  textCursor.insertList(QTextListFormat::ListDisc);
  textCursor.insertText("list item");
  textCursor.insertBlock();

  QTextListFormat listFormat;
      listFormat.setIndent(2);

      //listFormat.setProperty(QTextFormat::FontPointSize, 24);

      listFormat.setStyle(QTextListFormat::ListCircle);


  //textCursor.insertList(QTextListFormat::ListCircle);
  textCursor.insertText("second item");
  textCursor.insertBlock();
  textCursor.insertBlock();
  textCursor.insertText("horst");

  QTextTableFormat tableFormat;
  tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
  tableFormat.setCellSpacing(0);
  tableFormat.setBorder(1);
  tableFormat.setCellPadding(10);
  //tableFormat.setMargin(20);

  QTextTable* textTable = textCursor.insertTable(4, 3, tableFormat);

  //QTextCharFormat normal;
  //QTextCharFormat header;
  //header.setBackground(QBrush(QColor(Qt::gray)));

  for (int r = 0; r < textTable->rows(); ++r)
    for (int c = 0; c < textTable->columns(); ++c)
      textTable->cellAt(r, c).firstCursorPosition().insertText(QString("row: %1, column: %2").arg(r).arg(c));

  textCursor.currentTable()->setFormat(tableFormat);

  /*QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", QString(), "*.pdf");
      if (!fileName.isEmpty()) {
           if (QFileInfo(fileName).suffix().isEmpty())
               fileName.append(".pdf");
           QPrinter printer(QPrinter::HighResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setOutputFileName(fileName);
           ui->textEdit->document()->print(&printer);
      }*/
}

MainWindow::~MainWindow()
{
  delete ui;
}
