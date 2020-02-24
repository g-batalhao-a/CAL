/*
 * Change.cpp
 */

#include <iostream>
#include <vector>
#include "Change.h"

string calcChange(int m, int numCoins, int *coinValues)
{
    if(m==0){
        return "";
    }

    int lastCoin[m+1];
    int minCoin[m+1];

    fill_n(minCoin,m+1,0);
    fill_n(lastCoin,m+1,0);

    for(int i=1;i<=numCoins;i++){
        for(int k=coinValues[i-1];k<=m;k++){
            if(minCoin[k]==0||1+minCoin[k-coinValues[i-1]]<minCoin[k]){
                minCoin[k]=1+minCoin[k-coinValues[i-1]];
                lastCoin[k]=coinValues[i-1];
;            }
        }
    }
    string out="";
    int temp=m;
    if(minCoin[m]==0){
        return "-";
    }

    for(int i=0;i<minCoin[m];i++){
        out+=to_string(lastCoin[temp])+";";
        temp-=lastCoin[temp];
    }

    return out;

}


