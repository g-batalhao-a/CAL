#ifndef ENTREGA_II_PRISONER_H
#define ENTREGA_II_PRISONER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <util/Time.h>

using namespace std;

/**
 * @brief Prisoner Class
 */
class Prisoner {
private:
    int id;
    string name;
    int age;

    /**
     * @brief Destiny node id
     */
    int dest;
    /**
     * @brief Delivery Time
     */
    Time deliveryTime;

public:
    Prisoner(int id, string name, int age, int dest, Time deliveryTime);

    int getID();
    string getName();
    int getAge();
    int getDest();
    Time getDeliveryTime() const;
};

#endif //ENTREGA_II_PRISONER_H
