#ifndef ENTREGA_II_VEHICLES_H
#define ENTREGA_II_VEHICLES_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "prison/Prisoner.h"
using namespace std;

class Vehicle {
private:
    int capacity;
    int maxVelHighWay;
    int maxVelRoad;
    vector<Prisoner*> prisoners;
public:
    Vehicle(int capacity, int maxVelHighWay, int maxVelRoad);
    virtual ~Vehicle();

    const vector<Prisoner*> & getPrisoners() const;

    void addPrisoner(Prisoner *prisoner);
    bool removePrisoner(Prisoner *prisoner);
    bool isAtMaxCapacity();
    friend ostream& operator<<(ostream& os, const Vehicle& dt);
};

class Car : public Vehicle
{
public:
    Car(int capacity);
    virtual ~Car();
};

class Bus : public Vehicle
{
public:
    Bus(int capacity);
    virtual ~Bus();
};

#endif //ENTREGA_II_VEHICLES_H
