#ifndef OptionsDialog_h
#define OptionsDialog_h

#include <QDialog>

class QSettings;

namespace Ui
{
  class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit OptionsDialog(QSettings* settings, QWidget* parent = 0);
    ~OptionsDialog();

  private:
    Ui::OptionsDialog* ui;
    QSettings* m_settings;
};

#endif
