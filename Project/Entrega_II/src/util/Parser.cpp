#include "Parser.h"

void parseMap(Graph<coord> &graph, const string &location, bool grid) {

    string node_file;
    string edge_file;
    string loc = location.substr(0,location.find('_'));

    if (grid) {
        node_file = "../Mapas/GridGraphs/GridGraphs/" + location + "/nodes.txt";
        edge_file = "../Mapas/GridGraphs/GridGraphs/" + location + "/edges.txt";
    }
    else {
        node_file = "../Mapas/"+loc+"/"+location+"_nodes_xy.txt";
        edge_file = "../Mapas/"+loc+"/"+location+"_edges.txt";
    }

    if (location == "16x16")
        parseHighways(graph, location);

    if (!grid && loc=="porto") {
        parseTag(graph, "Policia");
        parseTag(graph, "Prisoes");
        parseTag(graph, "Tribunais");
    }

    string line;

    ifstream node;
    node.open(node_file);
    if (!node.is_open()) { cout<<"Couldn't open node file\n"; }

    getline(node, line);
    int num_nodes = stoi(line);

    for (int i = 0; i < num_nodes; i++) {
        getline(node, line);
        stringstream ss(line);
        string temp;
        int id, tag; double x, y;
        getline(ss,temp,'(');
        getline(ss,temp,',');
        id=stoi(temp);
        getline(ss,temp,',');
        x=stod(temp);
        getline(ss,temp,',');
        y=stod(temp);
        tag=0;
        for (auto idH : graph.getHighways()) {
            if (idH == id)
                tag = 2;
        }
        for(auto p : graph.getPOIs()){
            if(p->getID() == id)
                tag=1;
        }
        graph.addVertex(id,make_pair(x, y),tag);

    }
    node.close();

    ifstream edge;
    edge.open(edge_file);

    if (!edge.is_open()) { cout<<"Couldn't open edge file"; }

    getline(edge, line);
    int num_edges = stoi(line);
    for (int i = 0; i < num_edges; i++) {
        getline(edge, line);
        stringstream ss(line);
        string temp;
        int o, d;
        getline(ss,temp,'(');
        getline(ss,temp,',');
        o=stoi(temp);
        getline(ss,temp,',');
        d=stoi(temp);
        double weight = euclideanDistance(graph.findVertex(o)->getInfo(), graph.findVertex(d)->getInfo());
        if (graph.findVertex(o)->getTag() == 2 && graph.findVertex(d)->getTag() == 2)
            weight /= (120.0 * 1000 / 3600);
        else
            weight /= (50.0 * 1000 / 3600);
        graph.addEdge(o, d, weight);
        if (grid)
            graph.addEdge(d, o, weight);
    }
    edge.close();
}

void parseTag(Graph<coord> &graph, const string &location) {
    string tag_file = "../Mapas/Tags/tags"+location+".txt";
    string line;

    ifstream tag;
    tag.open(tag_file);
    if (!tag.is_open()) { cout<<"Couldn't open tag file\n"; }

    while(!tag.eof()){
        getline(tag, line);
        string name = line;
        getline(tag, line);
        int id = stoi(line);
        graph.addPOI(name,id);
    }

    tag.close();

}

void parseHighways(Graph<coord> &graph, const string &location) {
    string tag_file = "../Mapas/Tags/highways_"+location+".txt";
    string line;

    ifstream tag;
    tag.open(tag_file);
    if (!tag.is_open()) { cout<<"Couldn't open tag file\n"; }

    getline(tag, line);
    int num_tags = stoi(line);
    vector<int> ids;
    for (int i = 0; i < num_tags; i++) {
        getline(tag, line);
        int id=stoi(line);
        ids.push_back(id);
    }
    graph.setHighways(ids);

    tag.close();

}
