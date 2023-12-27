#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStackedWidget>
#include<QVBoxLayout>
#include <QMainWindow>
#include <QLabel>
#include "building.h"
#include "elevatorp.h"

//This willll represent mostly the waiting area where passenger wait for the elvators tto come to their floor
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void openEP(Elevator*, Passenger* );
    void openMainWindow();


    void on_upRequest_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void handleFireSignal();
    void handlePO();

    void updateDisplay();

private:
    Ui::MainWindow *ui;
    Building b;
    QTimer *timer;
    QStackedWidget *stackedWidget;
    ElevatorP *elevatorPanel;
signals:
    void openElevatorPanelSignal();
};
#endif // MAINWINDOW_H
