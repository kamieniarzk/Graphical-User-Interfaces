#ifndef DAYDIALOG_H
#define DAYDIALOG_H
#include "mainwindow.h"
#include "event.h"
#include "eventdialog.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QDialog>
#include <QWidget>
#include <QLayout>
#include <QMap>

class DayDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DayDialog(QMap<QDate, QVector<Event>>* events, QDate date, QWidget *parent = nullptr);
    QDate getDate();
    void updateDialog();
    void sortEvents();
    static bool lessThanTime(const Event &e1, const Event &e2); //for sorting of the events vector
    bool eventExists(QDate date);

private:
    QDate date;
    QMap<QDate, QVector<Event>> *events;

private slots:
    void addEvent();
    void editEvent(int id);
    void deleteEvent(int id);


};

#endif // DAYDIALOG_H
