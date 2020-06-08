#ifndef ENTREGA_II_MENUS_H
#define ENTREGA_II_MENUS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <prison/Vehicle.h>
#include <util/Time.h>
#include "util/utils.h"
#include "prison/Prisoner.h"
#include "graph/Graph.h"
#include "gui/GUI.h"

using namespace std;

/***
 * @brief Main Menu
 * @return Option chose by the user
 */
int mainMenu();

/***
 * @brief Prisoner Menu
 * @return Option chose by the user
 */
int prisonerMenu();

/***
 * @brief Graph Menu
 * @return Option chose by the user
 */
int graphMenu();

/***
 * @brief Performance Menu
 * @return Option chose by the user
 */
int performanceMenu();

/***
 * @brief Print the prisoners in a readable way
 * @param vec Vector with the current prisoners
 */
void showCurrentPrisoners(vector<Prisoner*> vec);

/***
 * @brief Remove a prisoner of the current prisoners list
 * @param vec Prisoners Vector
 * @param vehiclesVec Vehicles Vector
 */
void removePrisoner(vector<Prisoner*> &vec, vector<Vehicle *> &vehiclesVec);

/***
 * @brief Print the vehicles in a readable way
 * @param vector Vector with the current vehicles
 */
void showCurrentVehicles(vector<Vehicle *> vector);

/***
 * @brief Create a new Vehicle
 * @param vector Vehicles vector to add the new vehicle
 * @return Pointer to the created vehicle, or nullptr if it wasn't created any
 */
Vehicle *addVehicle(vector<Vehicle *> &vector);

/***
 * @brief Remove a Vehicle
 * @param vector Vector with all the vehicles
 */
void removeVehicle(vector<Vehicle *> &vector);

/***
 * @brief Change Prisoner Vehicle of Transportation
 * @param prisonersVec Vector with prisoners
 * @param vehiclesVec Vector with vehicles
 */
void changePrisonersVehicle(vector<Prisoner *> &prisonersVec, vector<Vehicle *> &vehiclesVec);

/***
 * @brief Example Setup for easier and faster testing
 * @param prisonersVec Vector with prisoners
 * @param vehiclesVec Vector with vehicles
 */
void setupExample(vector<Prisoner *> &prisonersVec, vector<Vehicle *> &vehiclesVec);

/***
 * @brief Choose the graph to use
 * @param graphVec Vector with available graphs
 * @return Graph chose by the user
 */
Graph<coord> chooseGraph(vector<Graph<coord>> graphVec);

/***
 * @brief Function to calculate the best paths
 * @param graph Graph to search
 * @param originID Origin node
 * @param vehiclesVec Vector with vehicles which are going to get paths
 * @param time Variable to change the search method (true - search by prisoners delivery time, false - search for the shortest path)
 * @return Vector with a path for each vehicle and their corresponding departure time
 */
vector<pair<Path, Time>> getBestPaths(Graph<coord> graph, int originID, vector<Vehicle *> vehiclesVec, bool time);

/***
 * @brief Function to calculate the best path by departure time (the later the better)
 * @param graph Graph to search
 * @param originID Origin node
 * @param vehiclesVec Vector with vehicles which are going to get paths
 * @return Vector with a path for each vehicle and their corresponding departure time
 */
vector<pair<Path,Time>> getLatestDeparturePaths(Graph<coord> graph, int originID, vector<Vehicle *> vehiclesVec);

/***
 * @brief Funtion to show paths in graphViewer
 * @param gui GraphViewer interface class
 * @param paths Vector with every path and their corresponding departure time
 */
void showBestPaths(GUI gui, vector<pair<Path,Time>> paths);

/***
 * @brief Show graph points of interest
 * @param vec Vector with POIs
 */
template <class T>
void showPOIs(vector<POI<T>*> vec){
    cout<<"Point Of Interest (choose by ID)"<<endl;
    for(auto p:vec){
        cout<<p->toString()<<endl;
    }
}

/***
 * @brief Create a new prisoner
 * @param vec Prisoners vector to add the new one
 * @param graph Graph to get the available POIs
 * @param vehicles Vector with vehicles to choose one for the prisoner
 */
template <class T>
void addPrisoner(vector<Prisoner*> &vec, Graph<T> graph, vector<Vehicle*>& vehicles) {
    string name;
    int age, destiny;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "PRISONER" << endl;
    cout << "__________________________________________________\n" << endl;
    name = readString("Name: ");
    cout << "__________________________________________________\n" << endl;
    age = readInt("Age: ");
    cout << "__________________________________________________\n" << endl;
    cout << "Delivery Time" << endl;
    int hour, minute;
    Time deliveryTime;
    do {
        try {
            hour = readInt("Hours:");
            deliveryTime.setHour(hour);
            minute = readInt("Minutes:");
            deliveryTime.setMinute(minute);
            break;
        } catch (InvalidTime &e) { cout << e.what() << endl; }
    } while (true);
    cout << "__________________________________________________\n" << endl;
    destiny = choosePlace(graph.getPOIs(), "DESTINY");
    Prisoner *prisoner = new Prisoner(vec.size() + 1, name, age, destiny, deliveryTime);
    vec.push_back(prisoner);
    cout << "__________________________________________________\n";
    cout << setw(23) << right << "Vehicle" << endl;
    if (vehicles.empty() || allVehiclesFull(vehicles)) {
        cout << "There are no vehicles available" << endl;
        Vehicle *vehicle;
        do {
            vehicle = addVehicle(vehicles);
            if (vehicle == nullptr) cout << "You can't go back. You need to create a new vehicle!" << endl;
        } while (vehicle == nullptr);
        vehicle->addPrisoner(prisoner);
        cout << "Added Prisoner to new Vehicle!" << endl;
    } else {
        cout << "Choose existing vehicle or create a new one?\n1 - Existing\n2 - New one" << endl;
        int menuop = chooseMenuOption(2);
        if (menuop == 2) {
            Vehicle *vehicle;
            do {
                vehicle = addVehicle(vehicles);
                if (vehicle == nullptr) cout << "Invalid Input. Invalid option." << endl;
            } while (vehicle == nullptr);
            vehicle->addPrisoner(prisoner);
        } else if (menuop == 1) {
            showCurrentVehicles(vehicles);
            int menuop2 = chooseMenuOption(vehicles.size());
            if (menuop2 != 0) {
                Vehicle *vehicle = vehicles[menuop2 - 1];
                vehicle->addPrisoner(prisoner);
                cout << "Added Prisoner to existing Vehicle!" << endl;
            }
        }
    }
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "PRISONER CREATED" << endl;
    cout << "__________________________________________________\n" << endl;
    system("pause");
}

/**
 * @brief Choose a place
 * @param POIs Vector with available POIs
 * @param str Title of the place (can be 'Destiny' or 'Origin')
 * @return The id of the chose node
 */
template <class T>
int choosePlace(vector<POI<T>*> POIs, string str) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << str << endl;
    cout << "__________________________________________________\n" << endl;

    for (int i = 0; i < POIs.size(); i++) {
        cout << i + 1 << " - " << POIs[i]->getName() << endl;
    }
    cout << "\n0 - Exit (First Node by default)" << endl;
    cout << "__________________________________________________\n" << endl;

    int placeID = chooseMenuOption(POIs.size() + 1);

    while(placeID>POIs.size()){
        cout<<"Invalid option! Please try again"<<endl;
        placeID = readInt("ID number: ");
    }
    if(placeID==0)
        placeID = POIs[0]->getID();
    else
        placeID = POIs[placeID - 1]->getID();


    return placeID;
}

#endif //ENTREGA_II_MENUS_H
