#ifndef BUILDING_H
#define BUILDING_H
#include <iostream>
#include <vector>

#include "unit.h"

//This class is responsible to handle the request between the elevators and the passenger

class Building
{
public:
    Building(): elevatorId(0), passengerId(0), safeFloor(1){}
    void addElevator(int );
    void addPassenger(int);
    int respondRequest(Passenger);
    std::vector<Passenger> passengers;
    std::vector<Elevator> elevators;
private:
    int elevatorId;
    int passengerId;
    int safeFloor;

};

#endif // BUILDING_H
