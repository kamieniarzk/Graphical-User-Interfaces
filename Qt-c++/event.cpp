#include "event.h"


Event::Event()
{
    description = "no description";
}

Event::Event(QString dscrp, QTime t) :
    description(dscrp),
    time(t) {}

Event::Event(QString string) {
    QStringList list = string.split("\t");
    time = QTime::fromString(list[1]);
    description = list[2];
}



QString Event::getDescription() const{
    return this->description;
}

QTime Event::getTime() const{
    return this->time;
}

QString Event::toString() const{
    return (time.toString() + "\t" + description);
}
