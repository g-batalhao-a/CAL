/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort
	bool processing;       // auxiliary field used by isDAG

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

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
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
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

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	// DONE (4 lines)
	if(findVertex(in)==NULL){
	    Vertex<T> * v = new Vertex<T>(in);
	    this->vertexSet.push_back(v);
        return true;
	}
	// HINT: use the findVertex function to check if a vertex already exists
	return false;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	// DONE (6 lines)
	// HINT: use findVertex to obtain the actual vertices
	Vertex<T> * source=findVertex(sourc);
    Vertex<T> * destination=findVertex(dest);
	if(source!=NULL&&destination!=NULL){
	    source->addEdge(destination,w);
        return true;
	}
	// HINT: use the next function to actually add the edge
	return false;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	// DONE (1 line)
	this->adj.push_back(Edge<T>(d,w));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	// DONE (5 lines)
	// HINT: Use "findVertex" to obtain the actual vertices.
    Vertex<T> * source=findVertex(sourc);
    Vertex<T> * destination=findVertex(dest);
    if(source!=NULL&&destination!=NULL){
        return source->removeEdgeTo(destination);
    }
	// HINT: Use the next function to actually remove the edge.
	return false;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	// DONE (6 lines)
	// HINT: use an iterator to scan the "adj" vector and then erase the edge.
	typename vector<Edge<T>>::iterator itr=adj.begin();
	while(itr!=adj.end()){
	    if((*itr).dest == d){
	        adj.erase(itr);
            return true;
	    }
	    itr++;
	}
	return false;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
	// DONE (10 lines)
	// HINT: use an iterator to scan the "vertexSet" vector and then erase the vertex.
	// HINT: take advantage of "removeEdgeTo" to remove incoming edges.
    typename vector<Vertex<T>*>::const_iterator itr=vertexSet.begin(); //iterator
    typename vector<Vertex<T>*>::const_iterator pos_to_rem=vertexSet.begin(); //iterator to position of vertex to be removed
    Vertex<T> * to_rem=findVertex(in);
    if(to_rem!=NULL){
        while(itr!=vertexSet.end()){
            if((*itr)!=to_rem){(*itr)->removeEdgeTo(to_rem);}
            else{pos_to_rem=itr;}
            itr++;
        }
        vertexSet.erase(pos_to_rem);
        return true;
    }

	return false;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
	// DONE (7 lines)
	vector<T> res;
	for(Vertex<T> *vertex:this->vertexSet){
	    vertex->visited=false;
	}
	for(Vertex<T> *vertex1:this->vertexSet){
	    if(!vertex1->visited)
	        dfsVisit(vertex1,res);
	}
	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	// DONE (7 lines)
	v->visited=true;
	res.push_back(v->info); //inserts the vertex
	for(Edge<T> edge:v->adj){
	    if(!edge.dest->visited){
	        dfsVisit(edge.dest,res);
	    }
	}
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	// DONE (22 lines)
	// HINT: Use the flag "visited" to mark newly discovered vertices .
	// HINT: Use the "queue<>" class to temporarily store the vertices.
	vector<T> res; queue<Vertex<T>*> aux;
	for(Vertex<T> *vertex:vertexSet){vertex->visited=false;} //no visited
    Vertex<T> *vertex= findVertex(source);  //Find Source Vertex
    aux.push(vertex);                       //Put in queue
	vertex->visited=true;                   //Mark as visited

	while(!aux.empty()){
	    vertex=aux.front();                 //Get Vertex
	    aux.pop();                          //Pop from auxiliary queue
	    res.push_back(vertex->info);        //Put into info vector
	    for(Edge<T> edges: vertex->adj){    //Search for Edges
	        if(!edges.dest->visited){       //If not previously visited
	            aux.push(edges.dest);       //Put into queue for posterior processing
	            edges.dest->visited=true;   //Mark as visited
	        }
	    }
	}
	return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
	// DONE (26 lines)
	vector<T> res;
	for(Vertex<T>* vertex:vertexSet){vertex->indegree=0;} //Base step: Everything at 0 degree
    for(Vertex<T>* vertex:vertexSet){
        for(Edge<T> edges: vertex->adj){edges.dest->indegree+=1;}   //"Child" Vertexes put in the next degree
    }

    queue<Vertex<T>*> c;
    for(Vertex<T>* vertex:vertexSet){if(vertex->indegree==0)c.push(vertex);} //Auxiliary queue with the "base cases"

    list<Vertex<T>*> t;     //List with the final Vertexes
    Vertex<T> *vertex;
    while(!c.empty()){      //Similar to BFS
        vertex=c.front();
        c.pop();
        t.push_back(vertex);
        res.push_back(vertex->info);
        for(Edge<T> edges:vertex->adj){
            edges.dest->indegree-=1;
            if(edges.dest->indegree==0){    //Verifies if there is a loop
                c.push(edges.dest);         //If it checks out, eventually the vertexSet
            }                               //and our auxiliary vector will disagree in size
        }
    }
    if(t.size()!=vertexSet.size()){cout<<"Graph has cycles\n";res.clear();}
	return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
	// DONE (28 lines, mostly reused)
    vector<T> res; queue<Vertex<T>*> aux; vector<Vertex<T>*> mostfriends; //New vector is the amount of new friends (that haven't been visited previously)
    int group_friends;
    for(Vertex<T> *vertex:vertexSet){vertex->visited=false;} //no visited
    Vertex<T> *vertex= findVertex(source);  //Find Source Vertex
    aux.push(vertex);                       //Put in queue
    vertex->visited=true;                   //Mark as visited
    group_friends=vertex->adj.size();
    while(!aux.empty()){
        vertex=aux.front();                 //Get Vertex
        aux.pop();                          //Pop from auxiliary queue
        res.push_back(vertex->info);        //Put into info vector
        for(Edge<T> edges: vertex->adj){    //Search for Edges
            if(!edges.dest->visited){       //If not previously visited
                aux.push(edges.dest);       //Put into queue for posterior processing
                mostfriends.push_back(edges.dest);
                edges.dest->visited=true;   //Mark as visited
            }
        }
        if(mostfriends.size()>group_friends){group_friends=mostfriends.size();inf=vertex->info;} //If a new Person has more "undiscovered" friends
        mostfriends.clear();
    }

    return group_friends;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
	// DONE (9 lines, mostly reused)
	// HINT: use the auxiliary field "processing" to mark the vertices in the stack.
    for(Vertex<T> *vertex:this->vertexSet){
        vertex->processing=false;
    }
    for(Vertex<T> *vertex1:this->vertexSet){
        if(!vertex1->visited)
            if(dfsIsDAG(vertex1)){ return true;};
    }
	return false;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	// DONE (12 lines, mostly reused)
    v->processing=true;
    for(Edge<T> edge:v->adj){
        if(!edge.dest->processing){
            return dfsIsDAG(edge.dest);
        }
        else{
            return false;
        }
    }
	return true;
}

#endif /* GRAPH_H_ */
