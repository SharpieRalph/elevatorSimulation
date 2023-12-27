#ifndef ELEVATORP_H
#define ELEVATORP_H

// This panel will simulate when an passenger enters into an elevaotr and it will show what you ususally see in an elevator panel.

#include <QWidget>
#include <unit.h>
#include <QTimer>
namespace Ui {
class ElevatorP;
}

class ElevatorP : public QWidget
{
    Q_OBJECT

public:
    explicit ElevatorP(QWidget *parent = nullptr);
    ~ElevatorP();
    void setElevator(Elevator* e, Passenger*);
    Elevator* getCurrElevator() const{ return elevator;}
    Passenger* getCurrPassenger() const{return passenger;}

private:
    Ui::ElevatorP *ui;
    Elevator *elevator;
    Passenger *passenger;
    QTimer *elevatorTimer;
signals:
    void exitSignal();
    void fireSignal();
private slots:
    void on_exitButton_clicked();
    void on_pushButton_5_clicked();
    void moveElevator();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_helpButton_clicked();
    void on_fireSignal_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
};

#endif // ELEVATORP_H
