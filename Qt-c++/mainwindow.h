#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMap>
#include "daydialog.h"
#include "event.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateEvents();
    void readDataFile();
    void setCurrentDateFormat();
    void saveDataToFile();

private:
    Ui::MainWindow *ui;
    QMap<QDate, QVector<Event>> events;

private slots:
    void dayClicked(const QDate date);
    void newDataFile();
    void openDataFile();
    void saveDataFile();
};

#endif // MAINWINDOW_H
