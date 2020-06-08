#ifndef ENTREGA_II_PARSER_H
#define ENTREGA_II_PARSER_H

#include <string>
#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include "graph/Graph.h"
#include "utils.h"

using namespace std;

/**
 * @brief Parse a map
 * @param graph Graph to load the map into
 * @param location Name of the map to load
 * @param grid True if is is a grid map (bidirectional edges) or False otherwise
 */
void parseMap(Graph<coord> &graph, const string &location, bool grid);

/**
 * @brief Parse tags
 * @param graph Graph to load the tags into
 * @param tag_file Name of the tag file
 */
void parseTag(Graph<coord> &graph,const string &tag_file);

/**
 * @brief Parse Highways
 * @param graph Graph to load the tags into
 * @param tag_file Name of the highway file
 */
void parseHighways(Graph<coord> &graph,const string &tag_file);

#endif //ENTREGA_II_PARSER_H
