#include <QDebug>

#include "PhoneBook.h"
#include "File.h"
#include "Path.h"

PhoneBook::PhoneBook(QObject* parent) :
  QAbstractTableModel(parent)
{
  QString configFile = Path::configurationFile("PhoneBook", "entries.txt");
  readFromFile(configFile);
}

int PhoneBook::rowCount(const QModelIndex& parent) const
{
  return m_entries.length();
}

int PhoneBook::columnCount(const QModelIndex& parent) const
{
  return PhoneBookEntry::numberOfAttributes();
}

QVariant PhoneBook::data(const QModelIndex& index, int role) const
{
  if (role == Qt::DisplayRole)
  {
    switch (index.column())
    {
      case 0:
        return m_entries[index.row()].abbreviation();

      case 1:
        return m_entries[index.row()].firstName();

      case 2:
        return m_entries[index.row()].lastName();

      case 3:
        return m_entries[index.row()].phoneNumber();

      case 4:
        return m_entries[index.row()].room();
    }
  }

  return QVariant();
}

QVariant PhoneBook::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal)
    {
      return PhoneBookEntry::header(section);
    }
  }

  return QVariant();
}

bool PhoneBook::setData(const QModelIndex& index, const QVariant& value, int role)
{
  return true;
}

Qt::ItemFlags PhoneBook::flags(const QModelIndex& index) const
{
  return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

// TODO should be in a seperate class "PhoneBookReader"
void PhoneBook::readFromFile(const QString& fileName)
{
  QStringList fileContent = File(fileName).toStringList();

  QString firstName;
  QString lastName;
  QString phoneNumber;
  QString room;
  QString abbreviation;
  QStringList splitted;

  int counter = 0;

  for (auto it = fileContent.begin(); it != fileContent.end(); ++it, ++counter)
  {
    if (it == fileContent.begin())
    {
      m_lastUpdate = QDate::fromString(*it, "yyyy-MM-dd");
    }
    else
    {
      int index = (counter - 1) % 4;

      if (index == 0)
      {
        abbreviation = *it;
      }
      else if (index == 1)
      {
        phoneNumber = *it;
      }
      else if (index == 2)
      {
        splitted = it->split(',');

        if (splitted.length() > 1)
        {
          lastName = splitted[0].trimmed();
          firstName = splitted[1].trimmed();
        }
      }
      else if (index == 3)
      {
        room = *it;
        m_entries.append(PhoneBookEntry(abbreviation, firstName, lastName, phoneNumber, room));
      }
    }
  }
}

int PhoneBook::numberOfEntries()
{
  return m_entries.length();
}

QDate PhoneBook::lastUpdate()
{
  return m_lastUpdate;
}
