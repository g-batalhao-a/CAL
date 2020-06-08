#ifndef ENTREGA_II_UTILS_H
#define ENTREGA_II_UTILS_H

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <chrono>
#include <vector>
#include <unordered_map>
#include "prison/Vehicle.h"
#include "graph/Graph.h"
#include <fstream>

using namespace std;

/**
 * @brief Returns a number between 0 and maxOption
 * @param maxOption Maximum number
 * @return Option chose by the user
 */
int chooseMenuOption(int maxOption);

/**
 * @brief Read an integer from the console
 * @param msg Message to print before each input
 * @return Read Integer
 */
int readInt(const string& msg);

/**
 * @brief Read a string from the console
 * @param msg Message to print before each input
 * @return Read String
 */
string readString(const string& msg);

/**
 * @brief Check if all vehicles are full
 * @param vehicles Vehicles vector
 * @return True if vehicles are full, False otherwise
 */
bool allVehiclesFull(vector<Vehicle*>& vehicles);

/**
 * @brief Euclidean distance between two points
 * @param point1 First Point coordinates
 * @param point2 Second Point coordinates
 * @return Euclidean Distance
 */
double euclideanDistance(pair<double, double> point1, pair<double, double> point2);

/**
 * @brief Function to compare ALT and A-Star algorithms run time
 * @param graph Graph to test
 * @param id_src Origin node ID
 * @param POIs Vector with points of interest
 * @param Prisoners Prisoners Vector
 */
void compareALT_AStar(Graph<coord> graph, int id_src, const vector<int>& POIs, const vector<Prisoner*>& Prisoners);

/**
 * @brief Function to compare ALT and Dijkstra algorithms run time
 * @param graph Graph to test
 * @param id_src Origin node ID
 * @param POIs Vector with points of interest
 */
void compareALT_Dijkstra(Graph<coord> graph, int id_src, const vector<int>& POIs);

/**
 * @brief Function to compare A-Star and Dijkstra algorithms run time
 * @param graph Graph to test
 * @param id_src Origin node ID
 */
void compareAStar_Dijkstra(Graph<coord> graph, const vector<int> &POIs);

/**
 * @brief Function to compare DFS and BFS algorithms run time in different sized graphs
 * @param graphs Vector with all graphs to test
 */
void compareDFS_BFS(const vector<Graph<coord>> &graphs);

/**
 * @brief Construct a new graph by a given path (all the vertices and their corresponding edges)
 * @param graph Graph to search the vertices
 * @param newGraph New Graph
 * @param path Path with nodes IDs
 */
void constructGraphByPath(const Graph<coord>& graph, Graph<coord>& newGraph, vector<int> path);

/**
 * @brief Sort prisoners vector by their delivery time
 * @param prisoners Prisoners Vector to be sorted
 */
void sortPrisonersByDeliveryTime(vector<Prisoner*> &prisoners);

/**
 * @brief Get the prisoners destinies
 * @param vec Vector with prisoners
 * @return Vector with destinies IDs
 */
vector<int> getPrisonersDestinies(vector<Prisoner*> vec);

/**
 * @brief Get departure time of a certain path
 * @param POIsTimes Map with prisoners POIs and the time to get there
 * @param prisoners Prisoners Vector
 * @return The latest departure time so that every prisoner arrives in time
 */
Time getDepartureTime(const unordered_map<int, Time> &POIsTimes, const vector<Prisoner*> &prisoners);

#endif //ENTREGA_II_UTILS_H
