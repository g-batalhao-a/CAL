/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

    double ** W = nullptr;
    int ** P = nullptr;
    int findVertexIdx(const T &in) const;
public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;
    ~Graph();

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //DONE...
	void dijkstraShortestPath(const T &s);      //DONE...
	void bellmanFordShortestPath(const T &s);   //DONE...
	vector<T> getPathTo(const T &dest) const;   //DONE...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for(Vertex<T>* vertex: vertexSet){
        vertex->dist=INT_MAX;
        vertex->path=NULL;
    }
    Vertex<T> * origin = findVertex(orig);
    origin->dist=0;
    queue<Vertex<T>*> shortestqueue;

    shortestqueue.push(origin);
    Vertex<T>* temp;
    while(!shortestqueue.empty()){
        temp=shortestqueue.front();
        shortestqueue.pop();
        for(Edge<T> edge: temp->adj){
            if(edge.dest->getDist()==INT_MAX){
                shortestqueue.push(edge.dest);
                edge.dest->dist=temp->getDist()+1;
                edge.dest->path=temp;
            }
        }
    }
	// DONE
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for(Vertex<T>* vertex: vertexSet){
        vertex->dist=INT_MAX;
        vertex->path=NULL;
    }
    Vertex<T> * og = findVertex(origin);
    og->dist=0;
    MutablePriorityQueue<Vertex<T>> dijkstratqueue;
    dijkstratqueue.insert(og);
    Vertex<T>* temp;
    while(!dijkstratqueue.empty()){
        temp=dijkstratqueue.extractMin();
        for(Edge<T> edge: temp->adj){
            if(edge.dest->getDist()>temp->getDist()+edge.weight){
                edge.dest->dist=temp->getDist()+edge.weight;
                edge.dest->path=temp;
                if(!dijkstratqueue.found(edge.dest))
                    dijkstratqueue.insert(edge.dest);
                else
                    dijkstratqueue.decreaseKey(edge.dest);
            }
        }
    }
	// DONE
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    for(Vertex<T>* vertex: vertexSet){
        vertex->dist=INT_MAX;
        vertex->path=NULL;
    }
    Vertex<T> * origin = findVertex(orig);
    origin->dist=0;

    for(int i=0;i<vertexSet.size();i++){
        for(Vertex<T> *temp: vertexSet){
            for(Edge<T> edge: temp->adj){
                if(edge.dest->getDist()>temp->getDist()+edge.weight){
                    edge.dest->dist=temp->getDist()+edge.weight;
                    edge.dest->path=temp;
                }
            }
        }
    }

    for(Vertex<T> *temp: vertexSet){
        for(Edge<T> edge: temp->adj){
            if(edge.dest->getDist()>temp->getDist()+edge.weight){
                cout<<"Negative Cycles"<<endl;
                break;
            }
        }
    }
	// DONE
}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
    vector<T> res;

    Vertex<T> *v = findVertex(dest);
    res.insert(res.begin(), v->info);

    do {
        v = v->path;
        res.insert(res.begin(), v->info);
    } while (v->path != NULL);

    return res;
}

/** Finds the index of the vertex with a given content.*/
template<class T>
int Graph<T>::findVertexIdx(const T &in) const{
    for(unsigned i = 0; i < vertexSet.size(); i++)
        if(vertexSet[i]->info == in)
            return i;
        return-1;
}

template<class T>
void deleteMatrix(T **m, int n) {
    if(m != nullptr) {
        for(int i = 0; i < n; i++)
            if(m[i] != nullptr)
                delete[] m[i];
            delete[] m;
    }
}
template<class T>
Graph<T>::~Graph() {
    deleteMatrix(W, vertexSet.size());
    deleteMatrix(P, vertexSet.size());
}

/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    // TODO
    unsigned n = vertexSet.size();
    deleteMatrix(W, n);
    deleteMatrix(P, n);
    W = new double*[n];
    P = new int*[n];
    for(unsigned i = 0; i < n; i++) {
        W[i] = new double[n];
        P[i] = new int[n];
        for(unsigned j = 0; j < n; j++) {
            W[i][j] = i == j? 0 : INF;
            P[i][j] = -1;}
        for(auto e : vertexSet[i]->adj) {
            int j = findVertexIdx(e.dest->info);
            W[i][j]  = e.weight;
            P[i][j]  = i;}
    }
    /*
    dist.clear();
    dist = vector<vector<double>>(vertexSet.size(), vector<double>(vertexSet.size(), INT64_MAX));
    pred.clear();
    pred = vector<vector<Vertex<T>*>>(vertexSet.size(), vector<Vertex<T>*>(vertexSet.size(), NULL));

    // Build dist matrix
    int i = 0, j = 0;
    for (auto v1 : vertexSet) {
        for (auto v2 : vertexSet) {
            if (i == j) {
                dist[i][j] = 0;
                pred[i][j] = v1;
            }
            else
                for (Edge<T> edge: v1->adj)
                    if (edge.dest->info == v2->info) {
                        dist[i][j] = edge.weight;
                        pred[i][j] = v1;
                    }
            j++;
        }
        i++;
        j = 0;
    }


    // Print Dist Matrix
    /*for (auto row : dist) {
        for (auto x : row) {
            cout << x << "\t";
        }
        cout << endl;
    }

    for (int k = 0; k < vertexSet.size(); k++) {
        int i = 0, j = 0;
        for (auto v1 : vertexSet) {
            for (auto v2 : vertexSet) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
                j++;
            }
            i++;
            j = 0;
        }
    }

    for (auto row : dist) {
        for (auto x : row) {
            cout << x << "\t";
        }
        cout << endl;
    }
    cout << endl << endl;
    for (auto row : pred) {
        for (auto x : row) {
            if (x != NULL)
                cout << x->getInfo() << "\t";
            else
                cout << "NULL\t";
        }
        cout << endl;
    }*/
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    vector<T> res;
    // TODO
    int i = findVertexIdx(orig);
    int j = findVertexIdx(dest);
    if(i == -1 || j == -1 || W[i][j] == INF) // missing or disconnected
        return res;
    for( ; j != -1; j = P[i][j])
        res.push_back(vertexSet[j]->info);
    reverse(res.begin(), res.end());
    return res;
    /*
    int srcIndex, destIndex, i = 0;

    for (auto x : vertexSet) {
        if (x->info == orig)
            srcIndex = i;
        else if (x->info == dest)
            destIndex = i;
        i++;
    }

    while (pred[srcIndex][destIndex] != vertexSet[srcIndex]) {
        res.insert(res.begin(), pred[srcIndex][destIndex]->info);
        i = 0;
        for (auto x : vertexSet) {
            if (x->info == pred[srcIndex][destIndex]->info)
                destIndex = i;
            i++;
        }
    }

    res.insert(res.begin(), orig);
    res.push_back(dest);

    return res;
     */
}



#endif /* GRAPH_H_ */
