#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->calendarWidget, SIGNAL(activated(QDate)), this, SLOT(dayClicked(QDate)));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newDataFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openDataFile()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveDataFile()));
    setCurrentDateFormat(); // formatting of current day cell
    readDataFile();         // reading data from default ":/data.txt" file
}

MainWindow::~MainWindow()
{
    saveDataToFile();
    delete ui;
}



// formatting of the days with events cells
void MainWindow::updateEvents() {
    QTextCharFormat dayFormat = ui->calendarWidget->dateTextFormat(QDate());
    //clearing all date formats
    ui->calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());
    dayFormat.setBackground(QBrush(QColor(165, 192, 255, 255)));
    QList<QDate> daysWithEvents = events.keys();
    for(int i = 0; i < daysWithEvents.size(); i++) {
        ui->calendarWidget->setDateTextFormat(daysWithEvents[i], dayFormat);
    }
    setCurrentDateFormat();
}

// formatting of the current day cell
void MainWindow::setCurrentDateFormat() {
    QTextCharFormat currDay = ui->calendarWidget->dateTextFormat(QDate::currentDate());
    currDay.setFontWeight(600);
    currDay.setFontPointSize(12);
    ui->calendarWidget->setDateTextFormat(QDate::currentDate(), currDay);
}

// slot for opening DayDialog window for clicked day
void MainWindow::dayClicked(const QDate date) {
    DayDialog *dialog = new DayDialog(&this->events, date, this);
    dialog->exec();
    updateEvents();
}

// slot for action
void MainWindow::newDataFile() {
    events.clear();
    updateEvents();
}

// slot for action
void MainWindow::openDataFile() {
    events.clear();
    QString fname = QFileDialog::getOpenFileName(this, "Open file");
    QFile file(fname);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString string;
    while(!in.atEnd()) {
        string = in.readLine(0);
        QStringList list = string.split("\t");
        QVector<Event> dayVec = events.value(QDate::fromString(list[0]));
        dayVec.push_back(Event(list[2], QTime::fromString(list[1])));
        events.insert(QDate::fromString(list[0]), dayVec);
    }
    file.close();
    updateEvents();
}

// slot for action
void MainWindow::saveDataFile() {
    QString fname = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fname);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QList<QDate> list = events.keys();
    for(int i = 0; i < list.size(); i++) {
        QVector<Event> dayVec = events.value(list[i]);
        for(int j = 0; j < dayVec.size(); j++) {
            out << list[i].toString() + "\t";
            out << dayVec.value(j).toString();
            out << "\n";
        }
    }
    file.close();
}


// after closing the program
void MainWindow::saveDataToFile() {
    QString fname = "data.txt";
    QFile file(fname);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QList<QDate> list = events.keys();
    for(int i = 0; i < list.size(); i++) {
        QVector<Event> dayVec = events.value(list[i]);
        for(int j = 0; j < dayVec.size(); j++) {
            out << list[i].toString() + "\t";
            out << dayVec.value(j).toString();
            out << "\n";
        }
    }
    file.close();
}

// at the program startup
void MainWindow::readDataFile() {
    QString fname = "data.txt";
    QFile file(fname);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        if(!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }
    }
    QTextStream in(&file);
    QString string;
    while(!in.atEnd()) {
        string = in.readLine(0);
        QStringList list = string.split("\t");
        QVector<Event> dayVec = events.value(QDate::fromString(list[0]));
        dayVec.push_back(Event(list[2], QTime::fromString(list[1])));
        events.insert(QDate::fromString(list[0]), dayVec);
    }
    file.close();
    updateEvents();
}
