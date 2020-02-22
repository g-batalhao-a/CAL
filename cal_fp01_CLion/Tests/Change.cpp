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
    string reg;
    int table[m+1];
    int lastCoin;
    vector<int> minCoin;
    table[0]=0;
    int amount=m;
    bool found=false;

    for(int x=0;x<numCoins;x++){
        if(coinValues[x]<=m){
            found=true;
        }
    }
    if(!found){
        return "-";
    }

    for(int i=1;i<=m;i++){
        table[i]=INT_MAX;
    }

    for(int i=1;i<=m;i++){ //ir de 1 a 9 (troco)
        for(int j=0;j<numCoins;j++){ //percorre as moedas
            if(coinValues[j]<=i){ //se o valor da moeda se encontra dentro do valor do troco
                int sub_res=table[i-coinValues[j]];
                if(sub_res!=INT_MAX && sub_res +1<table[i]){
                    table[i]=sub_res+1;
                }
            }
        }
    }
    int rem=1;
    bool done=false;
    do{
        for(int i=0;i<table[m];i++){
            for(int j=numCoins-rem;j>=0;j--){
                if(coinValues[j]<=amount){
                    cout<<coinValues[j]<<endl;
                    amount-=coinValues[j];
                    minCoin.push_back(coinValues[j]);
                    lastCoin=coinValues[j];
                    break;
                }
            }
        }
        if(amount!=0){
            amount=m;
            rem+=1;
            minCoin.clear();
        }
        else{
            done=true;
        }
    }while(!done);

    for(int x=0;x<minCoin.size();x++){
        reg+=to_string(minCoin[x])+";";
    }

    return reg;

}


