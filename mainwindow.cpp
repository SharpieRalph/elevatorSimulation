#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "elevatorp.h"
#include "unit.h"
#include <QThread>
#include <QTimer>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalSlider->setRange(1,4);
    ui->verticalSlider->setTickInterval(1);
    ui->verticalSlider->setTickPosition(QSlider::TicksRight);
    ui->verticalSlider_2->setRange(1,4);
    ui->verticalSlider_2->setTickInterval(1);
    ui->verticalSlider_2->setTickPosition(QSlider::TicksRight);
    ui->horizontalSlider->setRange(1,4);
    ui->horizontalSlider->setTickInterval(1);

    elevatorPanel = new ElevatorP(this);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(ui->centralwidget);
    stackedWidget->addWidget(elevatorPanel);

    connect(elevatorPanel, &ElevatorP::exitSignal, this, &MainWindow::openMainWindow);
    connect(elevatorPanel, &ElevatorP::fireSignal, this, &MainWindow::handleFireSignal);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);




}

MainWindow::~MainWindow()
{
    delete ui;
}


//Those 2 functions will alternate between the main widow and elevator panel when a passenger enters/exit the elevator
void MainWindow::openEP(Elevator * e, Passenger* p)
{
    elevatorPanel->setElevator(e, p);
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::openMainWindow()
{
    int newFloor = elevatorPanel->getCurrElevator()->getFloor();
    b.elevators[elevatorPanel->getCurrElevator()->getId()].updateFLoor(newFloor);
    b.passengers[0].updateFLoor(elevatorPanel->getCurrPassenger()->getFloor());
    ui->lcdNumber->display(b.elevators[0].getFloor());
    ui->lcdNumber_2->display(b.elevators[1].getFloor());
    ui->verticalSlider->setValue(b.elevators[0].getFloor());
    ui->verticalSlider_2->setValue(b.elevators[1].getFloor());
    ui->horizontalSlider->setValue(b.passengers[0].getFloor());
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()
{
  for(Elevator& e: b.elevators)
  {
      if(e.getFloor() == b.passengers[0].getFloor())
      {
          e.toggleIdling();
          this->openEP(&e, & b.passengers.at(0));
          qInfo("Door Opening");
          qInfo("Passenger enters elevator");
          qInfo("Door Closing");
      }
  }


}

void MainWindow::on_upRequest_clicked()
{
    qInfo("Up request received");
    ui->pushButton_2->setEnabled(false);

    updateDisplay();



    qInfo("Elevator arrived at correct floor");
    ui->pushButton_2->setEnabled(true);
}


void MainWindow::on_pushButton_2_clicked()
{
    qInfo("Down request received");

    ui->pushButton->setEnabled(false);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDisplay );
    timer->start(1000);


    qInfo("Elevator arrived at correct floor");
    ui->pushButton->setEnabled(true);
}


//->lcdNumber->display(e1.getFloor());
void MainWindow::on_pushButton_3_clicked()
{
    b.addElevator(ui->verticalSlider->value());
    b.addElevator(ui->verticalSlider_2->value());
    b.addPassenger(ui->horizontalSlider->value());
    ui->lcdNumber->display(b.elevators.at(0).getFloor());
    ui->lcdNumber_2->display(b.elevators.at(1).getFloor());

    //Disable the sliders
    ui->verticalSlider->setEnabled(false);
    ui->verticalSlider_2->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->pushButton_3->setEnabled(false);

}
void MainWindow::updateDisplay(){
    int index = b.respondRequest(b.passengers.at(0));

    if(index == 0){
         ui->lcdNumber->display(b.passengers.at(0).getFloor());
         b.elevators[0].updateFLoor(b.passengers.at(0).getFloor());
    }
    else{
         ui->lcdNumber_2->display(b.passengers.at(0).getFloor());
         b.elevators[1].updateFLoor(b.passengers.at(0).getFloor());
    }

}

void MainWindow::handleFireSignal(){
    qInfo("FIre signal received");
    ui->lcdNumber->display(b.elevators[0].getSafeFloor());
    ui->lcdNumber_2->display(b.elevators[1].getSafeFloor());
    ui->verticalSlider->setValue(b.elevators[0].getSafeFloor());
    ui->verticalSlider_2->setValue(b.elevators[1].getSafeFloor());

}

void MainWindow::handlePO(){
    qInfo("Power out signal received");
    ui->lcdNumber->display(b.elevators[0].getSafeFloor());
    ui->lcdNumber_2->display(b.elevators[1].getSafeFloor());
    ui->verticalSlider->setValue(b.elevators[0].getSafeFloor());
    ui->verticalSlider_2->setValue(b.elevators[1].getSafeFloor());

}
