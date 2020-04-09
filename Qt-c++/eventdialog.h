#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include "daydialog.h"
#include "ui_eventdialog.h"
#include "event.h"
#include <QMessageBox>
#include <QMap>

namespace Ui {
class EventDialog;
}

class EventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventDialog(QMap<QDate, QVector<Event>>* events, QDate date, bool add, QWidget* parent = nullptr, QTime time = QTime(), QString description = "");
    ~EventDialog();
    bool exists(QTime time, QString description) const;
private:
    Ui::EventDialog *ui;
    QDate date;
    QString description;
    QTime time;
    QMap<QDate, QVector<Event>> *events;
private slots:
    void closeWindow();
    void addEvent();
    void editEvent();
};

#endif // EVENTDIALOG_H
