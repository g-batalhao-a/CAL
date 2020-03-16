/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
	Result res;
	for(int x=0;x<vp.size();x++){
	    for(int y=x+1;y<vp.size();y++){
            double dist=vp[x].distance(vp[y]);
            if(dist<res.dmin){
                res.p1=vp[x];
                res.p2=vp[y];
                res.dmin=dist;
            }
	    }
	}
	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);
	// DONE
    for(int x=0;x<vp.size();x++){
        for(int y=x+1;y<vp.size();y++){
            double dist=vp[x].distance(vp[y]);
            if(dist<res.dmin){
                res.p1=vp[x];
                res.p2=vp[y];
                res.dmin=dist;
            }
        }
    }
	return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res){
    double dist;
    for(int i=left;i<right+1;i++){
        for(int j=i+1;j<right+1;j++){
            dist=vp[i].distance(vp[j]);
            if(abs(vp[i].y-vp[j].y)>res.dmin)
                break;
            else if(dist<res.dmin){
                res.dmin=dist;
                res.p1=vp[i];
                res.p2=vp[j];
            }
        }
    }
	// DONE (Explained in the end of the handout)
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
	// Base case of two points
	if(right-left==1){
        return Result(vp[left].distance(vp[right]),vp[left],vp[right]);
	}
	// DONE

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	if(right-left==0){
        return Result(MAX_DOUBLE,vp[left],vp[left]);
	}
	// DONE

	// Divide in halves (left and right) and solve them recursively,
    Result left_half, right_half;
	int mid = (left+right)/2;
	if(numThreads<=1){
        left_half=np_DC(vp,left,mid,numThreads);
        right_half= np_DC(vp,mid+1,right,numThreads);
	}
	// possibly in parallel (in case numThreads > 1)
	else if(numThreads>1){

	    std::thread t ([&vp,&left_half,left,mid,numThreads]{
	        vector<Point> v2(vp);
	        left_half=np_DC(v2,left,mid,numThreads/2);
	    });
	    right_half= np_DC(vp,mid+1,right,numThreads/2);
	    t.join();
	}
	// DONE

	// Select the best solution from left and right
	Result res;
	if(left_half.dmin<right_half.dmin)
	    res=left_half;
    else
        res=right_half;
	// DONE

	// Determine the strip area around middle point
	mid=(vp[right].x+vp[left].x)/2;
	int str_left = mid-res.dmin;
	int str_right = mid+res.dmin;
	// DONE (check end of handout)

	// Order points in strip area by Y coordinate
    int str_left_i=left;
    int str_right_i=right;

    for(int i=left;i<right;i++){
        if(vp[i].x<str_left)
            str_left_i=i;
        if(vp[i].x>str_right){
            str_right_i=i-1;
            break;
        }
    }

    sortByY(vp,str_left_i,str_right_i);
	// DONE

	// Calculate nearest points in strip area (using npByY function)
	npByY(vp,str_left_i,str_right_i,res);
	// DONE (Check end of handout for explanation on this function)

	// Reorder points in strip area back by X coordinate
	sortByX(vp,str_left_i,str_right_i);
	//DONE

	return res;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
