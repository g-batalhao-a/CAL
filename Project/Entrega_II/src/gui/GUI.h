#ifndef ENTREGA_II_GUI_H
#define ENTREGA_II_GUI_H

#include "../graphviewer/graphviewer.h"
#include "graph/Graph.h"

using namespace std;

/**
 * @brief Graph Viewer interface
 */
class GUI{
private:
    Graph<coord> graph;
    GraphViewer * gv;
    int gv_w;
    int gv_h;
public:
    GUI(Graph<coord> &graph,int w,int h);
    void setGraph(Graph<coord> &graph);
    Graph<coord> getGraph();

    /**
     * @brief Show the full graph
     */
    void show();

    /**
     * @brief Show graph and the paths given
     * @param shortestPath Vector with paths
     */
    void showMultiplePathsInMap(vector<Path> shortestPath);

    /**
     * @brief Create the GraphViewer
     */
    void createGV();

    /**
     * @brief Close the GraphViewer
     */
    void closeGV();

    /**
     * @brief Delete GraphViewer
     */
    void deleteGV();
};


#endif //ENTREGA_II_GUI_H
