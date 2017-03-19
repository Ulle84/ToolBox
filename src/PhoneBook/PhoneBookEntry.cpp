#include "PhoneBookEntry.h"

const QStringList PhoneBookEntry::m_headers = QStringList() << "abbreviation" << "first name" << "last name" << "phone number" << "room";

PhoneBookEntry::PhoneBookEntry()
{
}

PhoneBookEntry::PhoneBookEntry(const QString& abbreviation, const QString& firstName, const QString& lastName, const QString& phoneNumber, const QString& room) :
  m_abbreviation(abbreviation),
  m_firstName(firstName),
  m_lastName(lastName),
  m_phoneNumber(phoneNumber),
  m_room(room)
{
}

QString PhoneBookEntry::firstName()  const
{
  return m_firstName;
}

QString PhoneBookEntry::lastName() const
{
  return m_lastName;
}

QString PhoneBookEntry::phoneNumber() const
{
  return m_phoneNumber;
}

QString PhoneBookEntry::room() const
{
  return m_room;
}

void PhoneBookEntry::setFirstName(const QString& firstName)
{
  m_firstName = firstName;
}

void PhoneBookEntry::setLastName(const QString& lastName)
{
  m_lastName = lastName;
}

void PhoneBookEntry::setPhoneNumber(const QString& phoneNumber)
{
  m_phoneNumber = phoneNumber;
}

void PhoneBookEntry::setRoom(const QString& room)
{
  m_room = room;
}

QString PhoneBookEntry::abbreviation() const
{
  return m_abbreviation;
}

void PhoneBookEntry::setAbbreviation(const QString& abbreviation)
{
  m_abbreviation = abbreviation;
}

int PhoneBookEntry::numberOfAttributes()
{
  return m_headers.length();
}

QString PhoneBookEntry::header(int section)
{
  return m_headers.at(section);
}
