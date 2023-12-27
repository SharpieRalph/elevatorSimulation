#ifndef UNIT_H
#define UNIT_H

/*This will the passenger and levator classed. They will both have a unique id and a floor that keep track of their whereabout*/
class Unit
{
public:
    Unit(int n, int num2): floor(n), id(num2){}
    int getFloor() const {
        return floor;
    }
    void updateFLoor(int a);
    int getId() const{ return id;}

 private:
    int floor;
    int id;
};

class Passenger: public Unit{
public:
    Passenger(int n, int id): Unit(n, id){};
};

class Elevator: public Unit{
public:
    void goToPassenger();
    Elevator(int n, int id): Unit(n, id),  count(0), isIdle(true), floorRequested(0), safeFloor(1){}
    bool idling() const { return isIdle;}
    void toggleIdling() { isIdle = !isIdle;}
    int distanceToFloor(int floor) const;

    void setRequestedFloor(int n){ floorRequested = n;}
    int getRequestedFloor() const{return floorRequested;}
    int getSafeFloor(){ return safeFloor;}

private:
    int count;
    bool isIdle;
    int floorRequested;
    int safeFloor;

};
#endif // UNIT_H
