#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
// TODO: Implement here exercise 1!
    GraphViewer *gv = new GraphViewer(600, 600, true);
    gv->setBackground("../background.jpg");
    gv->createWindow(600, 600);

    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    gv->addNode(0);

    gv->addNode(1);

    gv->addEdge(0,0,1,EdgeType::UNDIRECTED);

    gv->removeNode(1);

    gv->addNode(2);

    gv->addEdge(1,0,2,EdgeType::UNDIRECTED);

    gv->setVertexLabel(2, "Cobre");

    gv->setEdgeLabel(1, "Isto e o teu cerebro em crack");

    gv->setVertexColor(2, "green");

    gv->setEdgeColor(1, "yellow");

    gv->rearrange();
}

void exercicio2()
{
// TODO: Implement here exercise 2!
    GraphViewer *gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);

    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    gv->addNode(0,300,50);
    gv->addNode(1,318,58);
    gv->addNode(2,325,75);
    gv->addNode(3,318,93);
    gv->addNode(4,300,100);
    gv->addNode(5,282,93);
    gv->addNode(6,275,75);
    gv->addNode(7,282,58);
    gv->addNode(8,150,200);
    gv->addNode(9,300,200);
    gv->addNode(10,450,200);
    gv->addNode(11,300,400);
    gv->addNode(12,200,550);
    gv->addNode(13,400,550);

    gv->addEdge(0,0,1,EdgeType::UNDIRECTED);
    gv->addEdge(1,1,2,EdgeType::UNDIRECTED);
    gv->addEdge(2,2,3,EdgeType::UNDIRECTED);
    gv->addEdge(3,3,4,EdgeType::UNDIRECTED);
    gv->addEdge(4,4,5,EdgeType::UNDIRECTED);
    gv->addEdge(5,5,6,EdgeType::UNDIRECTED);
    gv->addEdge(6,6,7,EdgeType::UNDIRECTED);
    gv->addEdge(7,7,0,EdgeType::UNDIRECTED);
    gv->addEdge(8,4,9,EdgeType::UNDIRECTED);
    gv->addEdge(9,9,8,EdgeType::UNDIRECTED);
    gv->addEdge(10,9,10,EdgeType::UNDIRECTED);
    gv->addEdge(11,9,11,EdgeType::UNDIRECTED);
    gv->addEdge(12,11,12,EdgeType::UNDIRECTED);
    gv->addEdge(13,11,13,EdgeType::UNDIRECTED);

    while(true){
        gv->rearrange();
        Sleep(1000);
        gv->removeNode(12);
        gv->removeNode(13);

        gv->addNode(14,250,550);
        gv->addNode(15,350,550);
        gv->addEdge(14,11,14,EdgeType::UNDIRECTED);
        gv->addEdge(15,11,15,EdgeType::UNDIRECTED);
        gv->rearrange();
        Sleep(1000);
        gv->removeNode(14);
        gv->removeNode(15);
        gv->addNode(12,200,550);
        gv->addNode(13,400,550);
        gv->addEdge(12,11,12,EdgeType::UNDIRECTED);
        gv->addEdge(13,11,13,EdgeType::UNDIRECTED);
    }



}

void exercicio3()
{
// TODO: Implement here exercise 3!
// To read map files, use relative paths:
// Vertices data: "../resources/mapa1/nos.txt"
// Edges data: "../resources/mapa1/arestas.txt"
    GraphViewer *gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);

    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    ifstream vertex("../resources/mapa1/nos.txt");
    string str;
    while (!vertex.eof()){
        int i,x,y;
        getline(vertex,str,';');
        i=stoi(str);
        getline(vertex,str,';');
        x=stoi(str);
        getline(vertex,str,'\n');
        y=stoi(str);
        gv->addNode(i,x,y);
    }

    ifstream edges("../resources/mapa1/arestas.txt");
    while (!edges.eof()){
        int i,x,y;
        getline(edges,str,';');
        i=stoi(str);
        getline(edges,str,';');
        x=stoi(str);
        getline(edges,str,'\n');
        y=stoi(str);
        gv->addEdge(i,x,y,EdgeType::UNDIRECTED);
    }
}

int main() {
    /*
     * Uncomment the line below to run Exercise 1
     */
    //exercicio1();

    /*
      * Uncomment the line below to run Exercise 2
      */
    //exercicio2();

    /*
      * Uncomment the line below to run Exercise 3
      */
	//
	exercicio3();

	getchar();
	return 0;
}
