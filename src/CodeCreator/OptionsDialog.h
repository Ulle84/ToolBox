#ifndef OptionsDialog_h
#define OptionsDialog_h

#include <QDialog>

class QSettings;

class OptionsDialogUi;

class OptionsDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit OptionsDialog(QSettings* settings, QWidget* parent = 0);
    ~OptionsDialog();

  private:
    OptionsDialogUi* ui;
    QSettings* m_settings;
};

#endif
