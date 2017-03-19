#include <QApplication>
#include <QClipboard>
#include <QString>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QString clipboardText = a.clipboard()->text();

  a.clipboard()->setText(clipboardText);

  return 0;
}
