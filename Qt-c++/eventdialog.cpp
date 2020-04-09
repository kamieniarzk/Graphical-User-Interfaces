#include "eventdialog.h"


EventDialog::EventDialog(QMap<QDate, QVector<Event>>* map, QDate date, bool add, QWidget* parent, QTime time, QString description) :
    QDialog(parent),
    ui(new Ui::EventDialog),
    date(date),
    description(description),
    time(time),
    events(map)
{
    ui->setupUi(this);
    setWindowTitle("Edit event");
    ui->setDescription->setText(description);
    ui->setTime->setTime(this->time);
    ui->dateLabel->setText(date.toString());
    ui->save->setDefault(true);
    connect(ui->cancel, SIGNAL(released()), this, SLOT(closeWindow()));
    //add is flag false if edit event, true if add event
    if(add) {
        connect(ui->save, SIGNAL(released()), this, SLOT(addEvent()));
    } else {
        connect(ui->save, SIGNAL(released()), this, SLOT(editEvent()));
    }
    connect(ui->save, SIGNAL(released()), this, SLOT(accept()));
    connect(ui->cancel, SIGNAL(released()), this, SLOT(reject()));
}

EventDialog::~EventDialog()
{
    delete ui;
}

void EventDialog::closeWindow() {
    this->close();
}

bool EventDialog::exists(QTime t, QString d) const{
    if(!events->contains(date)) {
        return false;
    } else {
        QVector<Event> dayVec = events->value(date);
        for(int i = 0; i < dayVec.size(); i++) {
            if(dayVec.value(i).getTime() == t && dayVec.value(i).getDescription() == d)
                return true;
        }
    }
    return false;
}

void EventDialog::addEvent() {
    if(!exists(ui->setTime->time(), ui->setDescription->text())){
        Event event = Event(ui->setDescription->text(), ui->setTime->time());
        QVector<Event> dayVec = events->value(date);
        dayVec.push_back(event);
        events->insert(date, dayVec);
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Event with given description and time already exists!");
    }
}



void EventDialog::editEvent() {
    if(events->contains(this->date)) {
        QVector<Event> dayVec = events->value(date);
        for(int i = 0; i < dayVec.size(); i++) {
            if(dayVec.value(i).getDescription() == this->description && dayVec.value(i).getTime() == this->time) {
                if(!exists(ui->setTime->time(), ui->setDescription->text())){
                    dayVec.remove(i);
                    Event event = Event(ui->setDescription->text(), ui->setTime->time());
                    dayVec.push_back(event);
                    events->insert(date, dayVec);
                    this->close();
                } else if(ui->setDescription->text() != this->description || ui->setTime->time() != this->time ){
                    QMessageBox::warning(this, "Error", "Event with given description and time already exists!");
                }
            }
        }
        this->close();
    } else {
        return;
    }
}
