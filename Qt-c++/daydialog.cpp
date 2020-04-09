#include "daydialog.h"
#include <QDesktopWidget>
#include <QTableWidget>
#include <QScrollArea>

DayDialog::DayDialog(QMap<QDate, QVector<Event>>* map, QDate date, QWidget* parent):
    QDialog(parent),
    date(date),
    events(map)
{
    setWindowTitle(date.toString(Qt::ISODate));
    updateDialog(); // builds the dialog using QScrollArea
    setMinimumSize(340, 250);
}



// slot
void DayDialog::addEvent() {
    EventDialog* dlg = new EventDialog(this->events, this->date, true, this);
    dlg->setModal(true);
    if(dlg->exec())
        this->updateDialog();
}

// slot
void DayDialog::editEvent(int id) {
    QVector<Event> dayVec = events->value(date);
    EventDialog* dlg = new EventDialog(this->events, this->date, false, this, dayVec.value(id).getTime(), dayVec.value(id).getDescription());
    dlg->setModal(true);
    if(dlg->exec())
        this->updateDialog();
}

// slot
void DayDialog::deleteEvent(int id) {
    if(events->contains(date)) {
        QVector<Event> dayVec = events->value(date);
        dayVec.remove(id);
        if(dayVec.size() > 0 ) {
            events->insert(date, dayVec);
        } else {
            events->remove(date);
        }
        this->updateDialog();
    }
}



QDate DayDialog::getDate() {
    return this->date;
}

// building the dialog layout with QScrollArea
void DayDialog::updateDialog() {
    qDeleteAll(this->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly)); // clearing previous layout
    delete layout();
    QVBoxLayout *gridLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QPushButton* add = new QPushButton("Add event", this);
    QPushButton* cancel = new QPushButton("Cancel", this);
    buttonLayout->addWidget(add);
    buttonLayout->addWidget(cancel);
    add->setDefault(true);
    connect(add, SIGNAL(released()), this, SLOT(addEvent()));
    connect(cancel, SIGNAL(released()), this, SLOT(close()));
    this->sortEvents();
    QGridLayout* grid = new QGridLayout();
    QHBoxLayout *eventsLayout = new QHBoxLayout;
    QButtonGroup* editButtons = new QButtonGroup(this);
    QButtonGroup* deleteButtons = new QButtonGroup(this);
    QLabel* timeLabel = new QLabel("Time", this);
    timeLabel->setStyleSheet("font-weight: bold;");
    timeLabel->setAlignment(Qt::AlignTop);
    QLabel* descriptionLabel = new QLabel("Description", this);
    descriptionLabel->setStyleSheet("font-weight: bold;");
    descriptionLabel->setAlignment(Qt::AlignTop);
    grid->addWidget(timeLabel, 0, 0);
    grid->addWidget(descriptionLabel, 0, 1);
    if(events->contains(date)) {
        QVector<Event> dayVec = events->value(date);
        for(int i = 0; i < dayVec.size(); i++) {
            grid->addWidget(new QLabel(dayVec.value(i).getTime().toString(), this), i + 1, 0);
            grid->addWidget(new QLabel(dayVec.value(i).getDescription(), this), i + 1, 1);
            editButtons->addButton(new QPushButton("Edit", this), i);
            editButtons->button(i)->setIcon(QIcon(":/edit.png"));
            deleteButtons->addButton(new QPushButton("Delete", this), i);
            deleteButtons->button(i)->setIcon(QIcon(":/img/trash.png"));
            grid->addWidget(editButtons->button(i), i + 1, 2);
            grid->addWidget(deleteButtons->button(i), i + 1, 3);
        }
    }
    grid->setAlignment(Qt::AlignTop);
    connect(editButtons, SIGNAL(buttonClicked(int)), this, SLOT(editEvent(int)));
    connect(deleteButtons, SIGNAL(buttonClicked(int)), this, SLOT(deleteEvent(int)));
    eventsLayout->addLayout(grid);
    eventsLayout->setSizeConstraint(QLayout::SetMaximumSize);
    gridLayout->addLayout(eventsLayout);
    QWidget *gridWidget = new QWidget(this);
    gridWidget->setLayout(gridLayout);
    QScrollArea *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setWidget(gridWidget);
    scroll->setAlignment(Qt::AlignHCenter);
    scroll->setAlignment(Qt::AlignTop);
    scroll->setMinimumSize(320,200);
    mainLayout->addWidget(scroll);
    mainLayout->addLayout(buttonLayout);
    this->setLayout(mainLayout);
}


// sorts the events vector
void DayDialog::sortEvents() {
    if(events->contains(date)) {
        QVector<Event> dayVec = events->value(date);
        std::sort(dayVec.begin(), dayVec.end(), lessThanTime);
        events->insert(date, dayVec);
    }
}

// comparison for sorting
bool DayDialog::lessThanTime(const Event &e1, const Event &e2) {
    return e1.getTime() < e2.getTime();
}

bool DayDialog::eventExists(QDate date) {
    return events->contains(date);
}


