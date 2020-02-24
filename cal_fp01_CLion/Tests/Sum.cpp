/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>

string calcSum(int* sequence, int size)
{
    string out="";

    int sum[size];
    fill_n(sum,size,INT_MAX);
    int min,minIndx;


    for(int m=1;m<=size;m++){
        min=INT_MAX;
        for(int i=0;i<=size-m;i++){
            if(m==1){
                sum[i]=sequence[i+m-1];
            }
            else{
                sum[i]=sum[i]+sequence[i+m-1];
            }
            if(sum[i]<min){
                min=sum[i];
                minIndx=i;
            }
        }
        out+=to_string(sum[minIndx])+","+to_string(minIndx)+";";
    }

	return out;
}

