#ifndef EVENT_H
#define EVENT_H
#include<QDate>
#include<QTime>


class Event
{
public:
    Event();
    Event(QString string);
    Event(QString dscrp, QTime t);

    QString getDescription() const;
    QTime getTime() const;
    QString toString() const;
private:
    QString description;
    QTime time;

};

#endif // EVENT_H
