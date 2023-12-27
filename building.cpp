#include "building.h"

void Building::addElevator(int a){
    elevators.push_back(Elevator(a, elevatorId++));

}

void Building::addPassenger(int a){
    passengers.push_back(Passenger(a, passengerId++));
}


int Building::respondRequest(Passenger p){
    int min = 10000000;
    int closestElevator = -1;

    for(size_t i =0; i<elevators.size(); ++i){
        if(elevators[i].idling()){
            int distance = elevators[i].distanceToFloor(p.getFloor());
            if(distance< min){
                min = distance;
                closestElevator = i;
            }
        }
    }
    return closestElevator;
}
