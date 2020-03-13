/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}


void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{
    initializeVisited();
    search(x,y);
    return foundSol;
}

void Labirinth::search(int x, int y) {
    // Check if solution already found
    if(foundSol) {return;}

    // Check if visited
    if(visited[x][y]) {return;}
    else{visited[x][y] = true;}
    // Out of Bounds
    if(x<0 || x>=10 || y<0 || y>=10) {return;}
    // Inside Wall
    if(labirinth[x][y] == 0) {return;}
    // Found Goal
    if(labirinth[x][y] == 2) {foundSol = true; return;}

    search(x+1 , y);search(x-1 , y);search(x , y+1);search(x , y-1);
}


