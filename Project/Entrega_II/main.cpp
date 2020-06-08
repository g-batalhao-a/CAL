#include <iostream>
#include <prison/Vehicle.h>


#include "menu/menus.h"
#include "src/util/Parser.h"
#include "src/gui/GUI.h"

using namespace std;

int main() {
    vector<Prisoner*> prisonerVec;
    vector<Vehicle*> vehiclesVec;

    int op,op2;

    Graph<coord> full,strong, penafiel_full, espinho_full, sixteen_grid,eight_grid,four_grid;
    parseMap(full, "porto_full", false);
    parseMap(strong, "porto_strong", false);
    parseMap(penafiel_full,"penafiel_full",false);
    parseMap(espinho_full,"espinho_full",false);
    parseMap(sixteen_grid, "16x16", true);
    parseMap(eight_grid, "8x8", true);
    parseMap(four_grid, "4x4", true);
    vector<Graph<coord>> graphVec = {full, strong};
    Graph<coord> graphSelect=chooseGraph(graphVec);

    vector<Graph<coord>> maps ={four_grid,eight_grid,sixteen_grid,penafiel_full,espinho_full,full};

    // Testar Conectividade e eliminar nodes nao necessarios
    Graph<coord> graphconnecteddfs;
    constructGraphByPath(graphSelect, graphconnecteddfs, graphSelect.dfs());
    Graph<coord> graphconnectedbfs;
    constructGraphByPath(graphSelect, graphconnectedbfs, graphSelect.bfs(1));

    //Choose Graph
    Graph<coord> graph=graphSelect;

    Path path;
    vector<int> pois;
    vector<Prisoner*> prisoners;
    vector<Path> paths;
    vector<vector<int>> pathsToDisplay;
    vector<int> conect;
    GUI fullMap = GUI(graph, 1900, 1000);
    GUI dfsMap = GUI(graphconnecteddfs,1900,1000);
    GUI bfsMap = GUI(graphconnectedbfs,1900,1000);

    // Choose Origin
    int originID = choosePlace(graph.getPOIs(), "ORIGIN"), newOrigin;
    if (originID == 0) return 0;

    while ((op = mainMenu()) != 0) {
        switch (op) {
            case 1:
                while((op2=prisonerMenu())!=0){
                    switch(op2) {
                        case 1:
                            addPrisoner(prisonerVec, graph, vehiclesVec);
                            sortPrisonersByDeliveryTime(prisonerVec);
                            break;
                        case 2:
                            removePrisoner(prisonerVec, vehiclesVec);
                            system("pause");
                            break;
                        case 3:
                            sortPrisonersByDeliveryTime(prisonerVec);
                            showCurrentPrisoners(prisonerVec);
                            system("pause");
                            break;
                        case 4:
                            addVehicle(vehiclesVec);
                            system("pause");
                            break;
                        case 5:
                            removeVehicle(vehiclesVec);
                            break;
                        case 6:
                            cout << "__________________________________________________\n" << endl;
                            cout << setw(23) << right << "List of Vehicles" << endl;
                            cout << "__________________________________________________\n" << endl;
                            showCurrentVehicles(vehiclesVec);
                            system("pause");
                            break;
                        case 7:
                            changePrisonersVehicle(prisonerVec, vehiclesVec);
                            system("pause");
                            break;
                        case 8:
                            setupExample(prisonerVec, vehiclesVec);
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 2:
                while((op2= graphMenu()) != 0){
                    switch(op2) {
                        case 1:
                            graph=chooseGraph(graphVec);
                            fullMap.setGraph(graph);
                            system("pause");
                            break;
                        case 2:
                            newOrigin = choosePlace(graph.getPOIs(), "ORIGIN");
                            if (newOrigin != 0) originID = newOrigin;
                            break;
                        case 3:
                            showPOIs(graph.getPOIs());
                            system("pause");
                            break;
                        case 4:
                            fullMap.show();
                            break;
                        case 5:
                            showBestPaths(fullMap, getBestPaths(fullMap.getGraph(), originID, vehiclesVec, false));
                            break;
                        case 6:
                            showBestPaths(fullMap, getBestPaths(fullMap.getGraph(), originID, vehiclesVec, true));
                            break;
                        case 7:
                            showBestPaths(fullMap, getLatestDeparturePaths(fullMap.getGraph(), originID, vehiclesVec));
                            break;
                        case 8:
                            dfsMap.show();
                            break;
                        case 9:
                            bfsMap.show();
                            break;
                        default:
                            break;
                    }
                }
                break;

            case 3:
                while((op2= performanceMenu()) != 0){
                    switch(op2) {
                        case 1:
                            pois = getPrisonersDestinies(prisonerVec);
                            compareALT_AStar(graph, originID, pois, prisonerVec);
                            system("pause");
                            break;
                        case 2:
                            pois = getPrisonersDestinies(prisonerVec);
                            compareALT_Dijkstra(graph, originID, pois);
                            system("pause");
                            break;
                        case 3:
                            compareAStar_Dijkstra(strong, strong.getPOIsbyID());
                            system("pause");
                            break;
                        case 4:
                            compareDFS_BFS(maps);
                            system("pause");
                            break;
                        default:
                            break;
                    }
                }
                break;
            default:
                break;
        }
    }

    return 0;
}


