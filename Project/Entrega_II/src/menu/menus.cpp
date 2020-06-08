#include "menus.h"

int mainMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "MAIN MENU" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << " 1 - Prisoner/Vehicle Menu" << endl;
    cout << " 2 - Graph Visualization" << endl;
    cout << " 3 - Algorithm Comparison" << endl;
    cout << endl << " 0 - Exit" << endl;
    cout << "__________________________________________________\n" << endl;

    return chooseMenuOption(3);
}

int prisonerMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "PRISONER MENU" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << " 1 - Add Prisoner" << endl;
    cout << " 2 - Remove Prisoner" << endl;
    cout << " 3 - See Current Prisoners" << endl;
    cout << " 4 - Add Vehicle" << endl;
    cout << " 5 - Remove Vehicle" << endl;
    cout << " 6 - Display Vehicles" << endl;
    cout << " 7 - Change Prisoner's Vehicle" << endl;
    cout << endl << " 8 - Example Setup" << endl;
    cout << endl << " 0 - Exit" << endl;
    cout << "__________________________________________________\n" << endl;
    return chooseMenuOption(8);
}

int graphMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "GRAPH MENU" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << " 1 - Change Type of Graph" << endl;
    cout << " 2 - Change Origin Point" << endl;
    cout << " 3 - Show Current POI'S" << endl;
    cout << " 4 - Show Full Graph" << endl;
    cout << " 5 - Show Shortest Path (Nearest Neighbour)" << endl;
    cout << " 6 - Show Shortest Path (Next Prisoner)" << endl;
    cout << " 7 - Show Path with Latest Departure Time" << endl;
    cout << " 8 - Show Connectivity" << endl;
    cout << " 9 - Show Connectivity from Origin" << endl;
    cout << endl << " 0 - Exit" << endl;
    cout << "__________________________________________________\n" << endl;
    return chooseMenuOption(9);
}

int performanceMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "ALGORITHMS MENU" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << " 1 - Compare ALT with A-Star" << endl;
    cout << " 2 - Compare ALT with Dijkstra" << endl;
    cout << " 3 - Compare Dijkstra with A-Star" << endl;
    cout << " 4 - Compare DFS and BFS" << endl;
    cout << endl << " 0 - Exit" << endl;
    cout << "__________________________________________________\n" << endl;
    return chooseMenuOption(4);
}

void showCurrentPrisoners(vector<Prisoner*> vec) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "PRISONERS" << endl;
    cout << "__________________________________________________\n" << endl;
    int i = 1;
    if (!vec.empty())
        for (Prisoner * p : vec)
            cout << i++ << " - " << p->getName() << " (ID: " << p->getID() << ") | Delivery Time: " << p->getDeliveryTime().toString(false) << " | Destination Node Id: " << p->getDest() << endl;
    else
        cout << "No prisoners to transport." << endl;
    cout << "__________________________________________________\n" << endl;
}

void removePrisoner(vector<Prisoner *> &vec, vector<Vehicle *> &vehiclesVec) {
    showCurrentPrisoners(vec);
    cout << "0 - Exit\n\n";

    int index = chooseMenuOption(vec.size());

    if (index > 0){
        Prisoner* prisoner = vec.at(index-1);
        vec.erase(vec.begin() + index - 1);
        int indexx = 0;
        for (int i = 0; i < vehiclesVec.size(); i++) {
            auto it = std::find_if(vehiclesVec[i]->getPrisoners().begin(),
                                   vehiclesVec[i]->getPrisoners().end(),
                                   [&](auto p) { return p->getID() == prisoner->getID(); });
            if (it != vehiclesVec[i]->getPrisoners().end()){
                indexx = i;
                break;
            }
        }
        vehiclesVec.at(indexx)->removePrisoner(prisoner);
    }
}

void showCurrentVehicles(vector<Vehicle *> vector) {
    if (vector.empty())
        cout << "No available Vehicles" << endl;
    else {
        for (int i = 0; i < vector.size(); ++i) {
            string type = dynamic_cast<Car*>(vector[i]) != nullptr ? "Car" : "Bus";
            cout << " " << i + 1 << " - " << type << " - " << *vector[i] << endl;
        }
    }
    cout << "__________________________________________________\n" << endl;
}

Vehicle *addVehicle(vector<Vehicle *> &vector) {
    cout << "Choose type of Vehicle:\n1 - Car\n2 - Bus" << endl;
    int menuop = chooseMenuOption(2);
    while (menuop == 0) menuop = chooseMenuOption(2);
    if(menuop == 1) {
        cout << "Choose capacity (1 or 2)\n";
        int cap = chooseMenuOption(2);
        if (cap != 0) {
            Car *car = new Car(cap);
            vector.push_back(car);
            cout << "Vehicle created!\n";
            return car;
        }

    }
    else if (menuop == 2){
        cout << "Choose capacity (1 to 10)\n";
        int cap = chooseMenuOption(10);
        if (cap != 0) {
            Bus *bus = new Bus(cap);
            vector.push_back(bus);
            cout << "Vehicle created!\n";
            return bus;
        };
    }

    return nullptr;
}

void removeVehicle(vector<Vehicle *> &vector) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Remove Vehicles" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "Only Vehicles with no Prisoners can be removed.\n" << endl;
    showCurrentVehicles(vector);
    int menuop2 = chooseMenuOption(vector.size());
    if (menuop2 != 0) {
        if (vector.at(menuop2-1)->getPrisoners().empty()){
            vector.erase(vector.begin() + menuop2 - 1);
            cout << "Removed successfully!" << endl;
        } else {
            cout << "Vehicle is not empty!" << endl;
        }
        system("pause");
    }

}

void changePrisonersVehicle(vector<Prisoner *> &prisonersVec, vector<Vehicle *> &vehiclesVec) {
    if (vehiclesVec.size() > 1) {
        showCurrentPrisoners(prisonersVec);
        if (!prisonersVec.empty()) {
            int index = chooseMenuOption(prisonersVec.size()), indexToReject, index2;
            
            if (index > 0) {
                Prisoner *prisoner = prisonersVec.at(index - 1);
                cout << "Change to which Vehicle?" << endl;
                for (int i = 0; i < vehiclesVec.size(); i++) {
                    string type = dynamic_cast<Car *>(vehiclesVec[i]) != nullptr ? "Car" : "Bus";

                    auto it = std::find_if(vehiclesVec[i]->getPrisoners().begin(),
                                           vehiclesVec[i]->getPrisoners().end(),
                                           [&](auto p) { return p->getID() == prisoner->getID(); });

                    if (it == vehiclesVec[i]->getPrisoners().end())
                        cout << " " << i + 1 << " - " << type << " - " << *vehiclesVec[i] << endl;
                    else indexToReject = i + 1;

                    do {
                        index2 = chooseMenuOption(vehiclesVec.size());
                    } while (index2 == indexToReject);

                    if (!vehiclesVec.at(indexToReject - 1)->removePrisoner(prisoner))
                        cout << "Erro a remover Prisioneiro" << endl;
                    vehiclesVec.at(index2 - 1)->addPrisoner(prisoner);

                    cout << "Change made!" << endl;
                }
                cout << "0 - Exit\n\n";
            }
        } else cout << "No prisoners available" << endl;
    } else cout << "No available Vehicles to switch to" << endl;
}

void setupExample(vector<Prisoner *> &prisonersVec, vector<Vehicle *> &vehiclesVec) {
    prisonersVec.clear();
    vehiclesVec.clear();

    Prisoner * p1 = new Prisoner(prisonersVec.size() + 1, "Pedro Seixas", 19, 21947, Time(19));
    Prisoner * p2 = new Prisoner(prisonersVec.size() + 1, "Goncalo Alves", 19, 52539, Time(19,3));
    Prisoner * p3 = new Prisoner(prisonersVec.size() + 1, "Andre Gomes", 19, 40775, Time(19));

    Bus * v1 = new Bus(2);
    Car * v2 = new Car(1);

    v1->addPrisoner(p1);
    v1->addPrisoner(p2);
    v2->addPrisoner(p3);

    prisonersVec.push_back(p1);
    prisonersVec.push_back(p2);
    prisonersVec.push_back(p3);
    sortPrisonersByDeliveryTime(prisonersVec);

    vehiclesVec.push_back(v1);
    vehiclesVec.push_back(v2);

    cout << "SETUP DONE!" << endl;
}

Graph<coord> chooseGraph(vector<Graph<coord>> graphVec){
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "CHOOSE A GRAPH TO WORK ON" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << " 1 - Original Graph" << endl;
    cout << " 2 - Strongly Connected Graph " << endl;
    cout << "\n0 - Continue (Default Original)" << endl;
    cout << "__________________________________________________\n" << endl;

    int graphnum = chooseMenuOption(2);

    if(graphnum>0)
        return graphVec.at(graphnum-1);

    return graphVec.at(0);
}

vector<pair<Path, Time>> getBestPaths(Graph<coord> graph, int originID, vector<Vehicle *> vehiclesVec, bool time) {
    vector<pair<Path,Time>> paths;
    for (int i = 0; i < vehiclesVec.size(); i++){
        Path path;
        vector<Prisoner*> prisoners = vehiclesVec[i]->getPrisoners(); sortPrisonersByDeliveryTime(prisoners);
        vector<Prisoner*> temp = vehiclesVec[i]->getPrisoners(); sortPrisonersByDeliveryTime(temp);

        vector<int> POIs = getPrisonersDestinies(prisoners);
        path = graph.nearestNeighbourSearchAStar(originID, POIs, prisoners, path, euclideanDistance, time);

        Time departureTime = getDepartureTime(path.getPOIsTimes(), temp);

        paths.push_back(make_pair(path, departureTime));
    }
    return paths;
}

vector<pair<Path,Time>> getLatestDeparturePaths(Graph<coord> graph, int originID, vector<Vehicle *> vehiclesVec) {
    vector<pair<Path,Time>> paths;
    cout << "Shortest Path" << endl;
    vector<pair<Path,Time>> nearestNeighbourPaths = getBestPaths(graph, originID, vehiclesVec, false);
    cout << "Best Path by Prisoner Order" << endl;
    vector<pair<Path,Time>> nextPrisonerPaths = getBestPaths(graph, originID, vehiclesVec, true);
    for (int i = 0; i < vehiclesVec.size(); i++){
        pair<Path,Time> nearest = nearestNeighbourPaths.at(i);
        pair<Path,Time> next = nextPrisonerPaths.at(i);
        if (nearest.second < next.second) // The greater departure time the best
            paths.push_back(next);
        else
            paths.push_back(nearest);
    }
    return paths;
}

void showBestPaths(GUI gui, vector<pair<Path,Time>> paths) {
    vector<Path> showPaths;
    for (int i = 0; i < paths.size(); i++) {
        cout << "__________________________________________________" << endl;
        cout << setw(23) << right << "Vehicle " << i + 1 << endl;
        cout << "Departure Time: " << paths.at(i).second.toString(false) << endl;
        cout << "Nodes in Path: " << paths.at(i).first.getPath().size() << endl;
        showPaths.push_back(paths.at(i).first);
    }
    gui.showMultiplePathsInMap(showPaths);
}
