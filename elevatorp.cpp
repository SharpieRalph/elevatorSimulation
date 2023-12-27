
#include "elevatorp.h"
#include "ui_elevatorp.h"
ElevatorP::ElevatorP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElevatorP),
    elevator(nullptr),
    passenger(nullptr),
    elevatorTimer(new QTimer(this))
{
    ui->setupUi(this);

    // Connect the exitButton click to the slot for handling exit requests
    connect(ui->exitButton, &QPushButton::clicked, this, &ElevatorP::on_exitButton_clicked);
    connect(ui->fireSignal, &QCheckBox::stateChanged, this, &ElevatorP::on_fireSignal_stateChanged);

    // Connect the elevatorTimer timeout to the moveElevator slot
    connect(elevatorTimer, &QTimer::timeout, this, &ElevatorP::moveElevator);

    // Set the interval for elevator movement
    elevatorTimer->setInterval(1000);
}

ElevatorP::~ElevatorP()
{
    delete ui;
}

void ElevatorP::setElevator(Elevator* e, Passenger* p)
{
    elevator = e;
    passenger = p;

    ui->floor->display(elevator->getFloor());
}

void ElevatorP::on_exitButton_clicked()
{
    emit exitSignal();
}

void ElevatorP::on_pushButton_5_clicked()
{
    if (elevator) {
        // Set the requested floor in the elevator
        elevator->setRequestedFloor(1);

        // Start the elevatorTimer to simulate movement to the requested floor
        elevatorTimer->start();
    }
}


void ElevatorP::moveElevator()
{
    if (elevator) {
        // Simulate elevator movement logic
        int currentFloor = elevator->getFloor();
        int targetFloor = elevator->getRequestedFloor();

        // Assuming the elevator moves one floor at a time
        if (currentFloor < targetFloor) {
            elevator->updateFLoor(currentFloor+1);

        } else if (currentFloor > targetFloor) {
            elevator->updateFLoor(currentFloor-1);
        }

        // Update the LCD display with the current floor
        ui->floor->display(elevator->getFloor());

        // If the elevator reached the requested floor, stop the timer
        if (currentFloor == targetFloor) {
            elevatorTimer->stop();
        }
        passenger->updateFLoor(targetFloor);
    }

}

void ElevatorP::on_pushButton_2_clicked()
{
    if (elevator) {
        // Set the requested floor in the elevator
        elevator->setRequestedFloor(2);

        // Start the elevatorTimer to simulate movement to the requested floor
        elevatorTimer->start();
    }
}


void ElevatorP::on_pushButton_3_clicked()
{
    if (elevator) {
        // Set the requested floor in the elevator
        elevator->setRequestedFloor(3);

        // Start the elevatorTimer to simulate movement to the requested floor
        elevatorTimer->start();
    }
}




void ElevatorP::on_pushButton_4_clicked()
{
    if (elevator) {
        // Set the requested floor in the elevator
        elevator->setRequestedFloor(4);

        // Start the elevatorTimer to simulate movement to the requested floor
        elevatorTimer->start();
    }
}


void ElevatorP::on_helpButton_clicked()
{
    qInfo("Help button pressed");
    qInfo("Waiting response from building safety");
    if(ui->safety->isChecked())
    {
        qInfo("Connected to building safety");
        if(ui->pResponse->isChecked())
            qInfo("Calling 911");
    }
        qInfo("Calling 911");


}





void ElevatorP::on_fireSignal_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        emit fireSignal();
        elevator->setRequestedFloor(1);


        elevatorTimer->start();
    }
}


void ElevatorP::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        qInfo("Overload, please reduce the load");
    }
}


void ElevatorP::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        qInfo("Power outage signal");
        elevator->setRequestedFloor(1);


        elevatorTimer->start();
        qInfo("Please disembark elevator");
    }
}


void ElevatorP::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        qInfo("Obstacle Signal");
        qInfo("Please stay cleared of the closing door");
    }
}

