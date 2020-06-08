#include "GUI.h"

GUI::GUI(Graph<coord> &graph, int w, int h) : graph(graph), gv_w(w), gv_h(h) {
}

void GUI::setGraph(Graph<coord> &graph) { this->graph = graph; }

Graph<coord> GUI::getGraph() {
    return this->graph;
}

void GUI::show() {
    createGV();
    double yPercent, xPercent;
    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        yPercent = (vertex->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05;
        xPercent = (vertex->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;
        gv->addNode(vertex->getID(), (int)(xPercent*gv_w), (int)(yPercent*gv_h));
        if(vertex->getTag()==1){
            gv->setVertexLabel(vertex->getID(), graph.findPOI(vertex->getID())->getName());
            gv->setVertexSize(vertex->getID(), 15);
            gv->setVertexColor(vertex->getID(),"RED");
        }
        else{
            gv->setVertexLabel(vertex->getID(),""/*to_string(vertex->getID())*/);
            gv->setVertexSize(vertex->getID(), 5);
        }

    }

    int id = 0;
    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        for (Edge<coord>* edge : vertex->getOutgoing()) {
            gv->addEdge(id, vertex->getID(), edge->getDest()->getID(), EdgeType::DIRECTED);
            gv->setEdgeLabel(id, ""/*to_string(edge->getWeight())*/);
            if (vertex->getTag() == 2 && edge->getDest()->getTag() == 2) {
                gv->setEdgeColor(id, "BLUE");
                gv->setEdgeThickness(id, 5);
            }
            id++;
        }
    }

    gv->rearrange();
    closeGV();
}


void GUI::showMultiplePathsInMap(vector<Path> shortestPaths) {
    createGV();
    double yPercent, xPercent;
    vector<string> colours = {"ORANGE","MAGENTA","CYAN","GREEN","YELLOW","BLUE","RED","GRAY","PINK","BLACK","LIGHT_GRAY"};

    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        yPercent = (vertex->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05;
        xPercent = (vertex->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;

        gv->addNode(vertex->getID(), (int)(xPercent*gv_w), (int)(yPercent*gv_h));
        gv->setVertexSize(vertex->getID(), 5);
    }

    int id = 0;
    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        for (Edge<coord>* edge : vertex->getOutgoing()) {
            gv->addEdge(id, vertex->getID(), edge->getDest()->getID(), EdgeType::UNDIRECTED);
            gv->setEdgeThickness(id, 0.5);
            id++;
        }
    }

    int colour=0;
    for(auto shortestPath: shortestPaths) {
        vector<int> path = shortestPath.getPath();
        if (path.size() == 1) path.push_back(path[0]);
        gv->setVertexLabel(path[0], graph.findPOI(path[0])->getName());
        gv->setVertexColor(path[0], "GREEN");
        gv->setVertexSize(path[0], 15);

        unordered_map<int, Time> POIs = shortestPath.getPOIsTimes();

        for (int i = 0; i < path.size() - 1; i++) {
            if (POIs.find(path[i]) != POIs.end()) {
                gv->setVertexLabel(path[i], graph.findPOI(path[i])->getName());
                gv->setVertexSize(path[i], 15);
                gv->setVertexColor(path[i], "YELLOW");
            }
            gv->addEdge(id, path[i], path[i + 1], EdgeType::DIRECTED);
            gv->setEdgeColor(id, colours[colour]);
            gv->setEdgeThickness(id, 10);
            id++;
        }
        colour = (colour==colours.size()-1) ? 0 : colour+1;

        gv->setVertexLabel(path[path.size() - 1], graph.findPOI(path[path.size() - 1])->getName());
        gv->setVertexSize(path[path.size() - 1], 15);
        gv->setVertexColor(path[path.size() - 1], "YELLOW");
    }
    gv->rearrange();
    closeGV();
}

void GUI::deleteGV() {
    if(gv!= nullptr){
        gv->closeWindow();
        delete(gv);
    }
}

void GUI::createGV() {
    this->gv = new GraphViewer(gv_w, gv_h, false);
    gv->createWindow(gv_w, gv_h);
    gv->defineVertexColor("GRAY");
    gv->defineVertexSize(5);
    gv->defineEdgeCurved(false);
}

void GUI::closeGV() {
    cout << "Press Enter to exit graph viewer." << endl;
    int character = getchar();
    if (character == '\n') { // enter key is pressed
        deleteGV();
    }
    else
        cin.ignore(1000, '\n');
}
