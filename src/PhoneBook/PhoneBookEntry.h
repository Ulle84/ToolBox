#ifndef PHONEBOOKENTRY_H
#define PHONEBOOKENTRY_H

#include <QString>
#include <QStringList>

class PhoneBookEntry
{
  public:
    PhoneBookEntry();
    PhoneBookEntry(const QString& abbreviation, const QString& firstName, const QString& lastName, const QString& phoneNumber, const QString& room);

    QString firstName() const;
    void setFirstName(const QString& firstName);

    QString lastName() const;
    void setLastName(const QString& lastName);

    QString phoneNumber() const;
    void setPhoneNumber(const QString& phoneNumber);

    QString room() const;
    void setRoom(const QString& room);

    QString abbreviation() const;
    void setAbbreviation(const QString& abbreviation);

    static int numberOfAttributes();
    static QString header(int section);

  private:
    static const QStringList m_headers;

    QString m_firstName;
    QString m_lastName;
    QString m_phoneNumber;
    QString m_abbreviation;
    QString m_room;
};

#endif // PHONEBOOKENTRY_H