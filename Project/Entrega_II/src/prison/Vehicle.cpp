#include "Vehicle.h"

Vehicle::Vehicle(int capacity, int maxVelHighWay, int maxVelRoad) {
    this->capacity = capacity;
    this->maxVelHighWay = maxVelHighWay;
    this->maxVelRoad = maxVelRoad;
}

void Vehicle::addPrisoner(Prisoner *prisoner) {
    this->prisoners.push_back(prisoner);
}

bool Vehicle::isAtMaxCapacity() {
    return this->capacity == this->prisoners.size();
}

const vector<Prisoner*> &Vehicle::getPrisoners() const{
    return prisoners;
}

Car::Car(int capacity) : Vehicle(capacity, 120, 50) {
}

Car::~Car() {}

Bus::Bus(int capacity) : Vehicle(capacity, 90, 50) {
}

Bus::~Bus() {}

ostream& operator<<(ostream& os, const Vehicle& dt)
{
    os << "Capacity: " << dt.prisoners.size() << '/' << dt.capacity << " | Road Velocity: " << dt.maxVelRoad << " | Highway Velocity: " << dt.maxVelHighWay;
    return os;
}

Vehicle::~Vehicle() {}

bool Vehicle::removePrisoner(Prisoner *prisoner) {
    int indexToErase = -1;
    for (int i = 0; i < prisoners.size(); ++i) {
     if (prisoners.at(i) == prisoner){
         indexToErase = i;
         break;
     }
    }
    if (indexToErase == -1) return false;
    prisoners.erase(prisoners.begin() + indexToErase);
    return true;
}
