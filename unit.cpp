#include "unit.h"
#include <cmath>

int Elevator::distanceToFloor(int floor) const{
    return std::abs(this->getFloor() - floor);
}

void Unit::updateFLoor(int a){
    floor = a;
}
