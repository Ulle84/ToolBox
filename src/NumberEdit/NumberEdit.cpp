#include "NumberEdit.h"
#include "ui_NumberEdit.h"

NumberEdit::NumberEdit(QWidget* parent) :
  Gridable(parent),
  ui(new Ui::NumberEdit)
{
  ui->setupUi(this);
  ui->label->setVisible(false);
  ui->comboBox->setVisible(false);

  if (parent)
  {
    if (!(parent->property("gridableEventFilterInstalled").isValid() && parent->property("gridableEventFilterInstalled").toBool()))
    {
      gridableEventFilterInstalledByThisInstance = true;
      parent->installEventFilter(this);
      parent->setProperty("gridableEventFilterInstalled", true);
    }    
  }
}

NumberEdit::~NumberEdit()
{
  if (parent() && gridableEventFilterInstalledByThisInstance)
  {
    // TODO who takes the responsibilty of gridding if there are other instances of gridables?
    parent()->setProperty("gridableEventFilterInstalled", false);
  }

  delete ui;
}

void NumberEdit::setLabel(const QString& label)
{
  ui->label->setVisible(!label.isEmpty());
  ui->label->setText(label);
}

QString NumberEdit::label()
{
  return ui->label->text();
}

void NumberEdit::setUnit(const QString& unit)
{
  ui->comboBox->setVisible(!unit.isEmpty());
  ui->comboBox->clear();
  ui->comboBox->addItem(unit);
}

QString NumberEdit::unit()
{
  return ui->comboBox->currentText();
}

QVector<int> NumberEdit::minimumWidths()
{
  QVector<int> list;

  list.append(ui->gridLayout->cellRect(0, 0).width());
  list.append(0);
  list.append(ui->gridLayout->cellRect(0, 2).width());

  return list;
}

void NumberEdit::setMinimumWidths(const QVector<int>& minimumWidths)
{
  for (int i = 0; i < minimumWidths.length(); ++i)
  {
    if (i < ui->gridLayout->count())
      ui->gridLayout->setColumnMinimumWidth(i, minimumWidths[i]);
  }
}

void NumberEdit::resetMinimumWidths()
{
  for (int i = 0; i < ui->gridLayout->count(); ++i)
  {
    ui->gridLayout->setColumnMinimumWidth(i, 0);
  }
}

bool NumberEdit::eventFilter(QObject * watched, QEvent * event)
{
  // TODO find all event types, which are relevant
  if (event->type() == QEvent::Resize)// || event->type() == QEvent::ChildAdded || event->type() == QEvent::ChildRemoved)
  {
    //QList<QWidget *> widgets = watched.findChildren<QWidget *>("widgetname");
    QList<Gridable*> gridables = watched->findChildren<Gridable*>(QString(), Qt::FindDirectChildrenOnly);

    for (auto it = gridables.begin(); it != gridables.end(); ++it)
    {
      (*it)->resetMinimumWidths();
    }

    bool result = watched->event(event);

    QVector<int> minimumWidths;

    for (auto it = gridables.begin(); it != gridables.end(); ++it)
    {
      QVector<int> vec = (*it)->minimumWidths();

      for (int i = 0; i < vec.length(); ++i)
      {
        if (i >= minimumWidths.length())
          minimumWidths.resize(i + 1);

        if (vec[i] > minimumWidths[i])
          minimumWidths[i] = vec[i];
      }
    }

    for (auto it = gridables.begin(); it != gridables.end(); ++it)
    {
      (*it)->setMinimumWidths(minimumWidths);
    }

    return result;
  }

  return Gridable::eventFilter(watched, event);
}