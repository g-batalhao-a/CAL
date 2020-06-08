#include "Prisoner.h"

Prisoner::Prisoner(int id, string name, int age, int dest, Time deliveryTime) {
    this->id = id;
    this->name = name;
    this->age = age;
    this->dest = dest;
    this->deliveryTime = deliveryTime;
}

int Prisoner::getID() {
    return this->id;
}

string Prisoner::getName() {
    return this->name;
}

int Prisoner::getAge() {
    return this->age;
}

int Prisoner::getDest() {
    return this->dest;
}

Time Prisoner::getDeliveryTime() const {
    return this->deliveryTime;
}
