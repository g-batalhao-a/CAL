#include "utils.h"

int chooseMenuOption(int maxOption) {
    int op;

    do {
        op = readInt("Choose an option: ");
        if (op > maxOption || op < 0)
            cout << "Invalid Input. Invalid option." << endl;
    } while(op > maxOption || op < 0);

    return op;
}

int readInt(const string& msg) {
    string line;
    int num = 0;
    bool error;

    do
    {
        cout << msg;
        getline(cin, line);

        error = any_of(line.begin(), line.end(), ::isalpha); //Ver se tem alguma letra

        if (error)
            cout << "Invalid Input. Can not have letters." << endl;

        if (!error && line.empty()) {
            error = true;
            cout << "Empty Input. " << endl;
        }

        if (!error) {
            for (auto x : line) {
                if (isspace(x)) {
                    error = true;
                    break;
                }
            }
            if (error)
                cout << "Invalid Input. Can not have spaces." << endl;
        }

        if (!error) {
            try {
                num = stoi(line);
            }
            catch (invalid_argument&) { //Ver se tem caracter especial
                error = true;
                cout << "Invalid Input. Can not have special characters." << endl;
            }
            catch (out_of_range&) { //Ver se o numero e demasiado grande
                error = true;
                cout << "Invalid Input. Number is to big." << endl;
            }
        }

        if (!error && line.size() != to_string(stoi(line)).size()) {
            for (auto x : line) {
                if (ispunct(x)) {
                    error = true;
                    break;
                }
            }
            if (error)
                cout << "Invalid Input. Can not have special characters." << endl;
        }

    } while (error);

    num = stoi(line);
    return num;
}

string readString(const string& msg) {
    string line;
    bool error;
    size_t t;
    do
    {
        error = false;
        cout << msg;
        getline(cin, line);

        t = line.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -\n"); //Ver se tem algum caracter inválido
        if(t!=line.npos) error=true;
        if (error)
            cout << "Invalid Input. Can not have invalid characters." << endl;

        if (!error && line.empty()) {
            error = true;
            cout << "Empty Input. " << endl;
        }

    } while (error);

    return line;
}

bool allVehiclesFull(vector<Vehicle*>& vehicles) {
    for (int i = 0; i < vehicles.size(); ++i) {
        if (!vehicles[i]->isAtMaxCapacity())
            return false;
    }
    return true;
}

double euclideanDistance(pair<double, double> point1, pair<double, double> point2) {
    return sqrt(pow((point1.first - point2.first), 2) + pow((point1.second - point2.second), 2));
}

void compareALT_AStar(Graph<coord> graph, int id_src, const vector<int>& POIs, const vector<Prisoner*>& Prisoners) {
    Path path1, path2;
    vector<int> p1 = POIs, p2 = POIs;
    vector<Prisoner*>pr=Prisoners;
    auto t1 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourSearchALT(id_src, p1, path1);
    auto t2 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourSearchAStar(id_src, p2, pr, path2, euclideanDistance, false);
    auto t3 = chrono::high_resolution_clock::now();

    auto durationALT = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    auto durationAStar = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();

    cout << "Ran ALT Search in " << durationALT << " microseconds" << endl;
    cout << "Ran A-Star Search in " << durationAStar << " microseconds" << endl;
}

void compareALT_Dijkstra(Graph<coord> graph, int id_src, const vector<int>& POIs) {
    Path path1, path2;
    vector<int> p1 = POIs, p2 = POIs;
    auto t1 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourSearchALT(id_src, p1, path1);
    auto t2 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourDijkstra(id_src, p2, path2);
    auto t3 = chrono::high_resolution_clock::now();

    auto durationALT = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    auto durationDijkstra = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();

    cout << "Ran ALT Search in " << durationALT << " microseconds" << endl;
    cout << "Ran Dijkstra Search in " << durationDijkstra << " microseconds" << endl;
}

void compareAStar_Dijkstra(Graph<coord> graph, const vector<int> &POIs) {
    /*
    ofstream outputFile;
    string fileName = "AStarandDijkstraComparison.csv";
    outputFile.open(fileName);
    if(!outputFile.is_open()){
        cout<<"Couldn't open csv file!\n";
    }
    outputFile<<"Path Size;DurationAStar;DurationDijkstra\n";*/
    for(auto poi: POIs){
        for(auto poi2: POIs) {
            cout<<"Src: "<<poi<<" Dest: "<<poi2<<endl;
            Path path1, path2;
            vector<int> p1 = {poi2}, p2 = {poi2};
            auto *prisoner = new Prisoner(0, "test", 1, poi2, Time(12, 00));
            vector<Prisoner *> pr = {prisoner};
            auto t1 = chrono::steady_clock::now();
            graph.nearestNeighbourSearchAStar(poi, p1, pr, path1, euclideanDistance, false);
            auto t2 = chrono::steady_clock::now();
            graph.nearestNeighbourDijkstra(poi, p2, path2);
            auto t3 = chrono::steady_clock::now();

            auto durationAStar = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
            auto durationDijkstra = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();

            cout << "Ran AStar Search in " << durationAStar << " microseconds" << endl;
            cout << "Ran Dijkstra Search in " << durationDijkstra << " microseconds" << endl;
            cout<<path1.getLength()<<" , "<<path2.getLength()<<" , "<<durationAStar<<" , "<<durationDijkstra<<"\n";
            //outputFile<< path1.getLength()<<";"<<durationAStar<<";"<<durationDijkstra<<"\n";
        }
    }
    //outputFile.close(); //UNCOMMENT FOR FILE OUTPUT

}

void compareDFS_BFS(const vector<Graph<coord>> &graphs) {
    /*
    ofstream outputFile;
    string fileName = "DFSandBFSComparison.csv";
    outputFile.open(fileName);
    if(!outputFile.is_open()){
        cout<<"Couldn't open csv file!\n";
    }
    cout<<graphs.size()<<endl;
    outputFile<<"Graph Size;DurationDFS;DurationBFS\n";
    */
    for(auto & graph : graphs){
        //cout<<"New Graph"<<endl;
        auto t1 = chrono::steady_clock::now();
        graph.dfs();
        //cout<<"Calculated DFS"<<endl;
        auto t2 = chrono::steady_clock::now();
        graph.bfs(graph.getVertexSet()[0]->getID());
        //cout<<"Calculated BFS"<<endl;
        auto t3 = chrono::steady_clock::now();

        auto durationDFS = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        auto durationBFS = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();

        cout << "Number of Vertices: " << graph.getVertexSet().size() << endl;
        cout << "DFS: " << durationDFS << "us \tBFS: " << durationBFS << "us" << endl << endl;
        //cout<<graph.getVertexSet().size()<<" , "<<durationDFS<<" , "<<durationBFS<<"\n";
        //outputFile<< graph.getVertexSet().size()<<";"<<durationDFS<<";"<<durationBFS<<"\n";
    }
    //outputFile.close(); //UNCOMMENT FOR FILE OUTPUT

}

void constructGraphByPath(const Graph<coord>& graph, Graph<coord>& newGraph, vector<int> path){
    Vertex<coord> * v1, *v2;
    for (int i = 0; i < path.size() - 1; i++) {
        v1 = graph.findVertex(path[i]);
        v2 = graph.findVertex(path[i+1]);
        newGraph.addVertex(v1->getID(), v1->getInfo(), v1->getTag());
        for(Edge<coord> * e : v1->getOutgoing()) {
            if (e->getDest() == v2) {
                newGraph.addVertex(v2->getID(), v2->getInfo(), v2->getTag());
                newGraph.addEdge(v1->getID(), v2->getID(), e->getWeight());
                break;
            }
        }
    }

    for(auto poi: graph.getPOIs()){
        newGraph.addPOI(poi);
    }
}

void sortPrisonersByDeliveryTime(vector<Prisoner*> &prisoners) {
    sort(prisoners.begin(), prisoners.end(), [](const Prisoner* left, const Prisoner* right) {
        return left->getDeliveryTime() < right->getDeliveryTime();
    });
}

vector<int> getPrisonersDestinies(vector<Prisoner*> vec){
    vector<int> des;
    for(auto p:vec){
        if(find(des.begin(),des.end(),p->getDest())==des.end())
            des.push_back(p->getDest());
    }
    return des;
}

Time getDepartureTime(const unordered_map<int, Time> &POIsTimes, const vector<Prisoner*> &prisoners) {
    cout << "Prisoner: " << prisoners[0]->getName() << " -> Node " << prisoners[0]->getDest() << " ( Time to get there: " <<  POIsTimes.at(prisoners[0]->getDest()).toString(true) << ")" << endl;
    Time departureTime(prisoners[0]->getDeliveryTime() - POIsTimes.at(prisoners[0]->getDest()));
    Time temp;

    for (int i = 1; i < prisoners.size(); i++) {
        cout << "Prisoner: " << prisoners[i]->getName() << " -> Node " << prisoners[i]->getDest() << " ( Time to get there: " <<  POIsTimes.at(prisoners[i]->getDest()).toString(true) << ")" << endl;
        temp = departureTime + POIsTimes.at(prisoners[i]->getDest());
        if (temp < prisoners[i]->getDeliveryTime())
            continue;
        else
            departureTime = departureTime - (temp - prisoners[i]->getDeliveryTime());
    }

    return departureTime;
}
