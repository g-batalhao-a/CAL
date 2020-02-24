/*
 * Partioning.cpp
 */

#include <iostream>
#include "Partitioning.h"


int s_recursive(int n,int k)
{
    if(k==1||k==n)
        return 1;
    else
        return s_recursive(n-1,k-1)+k*s_recursive(n-1,k);

}

int s_dynamic(int n,int k){
    int table[n+1][k+1];
    for(int x=0;x<=n;x++){
        table[x][0]=0;
    }
    for(int x=0;x<=k;x++){
        table[0][k]=0;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            if(j==1||i==j){
                table[i][j]=1;
                cout<<table[i][j]<<" ";
            }
            else{
                table[i][j]=j*table[i-1][j]+table[i-1][j-1];
                cout<<table[i][j]<<" ";
            }
        }
        cout<<"\n";
    }

	return table[n][k];
}


int b_recursive(int n) {
    /*if (n == 1 || n == 0)
        return 1;
    else
        return (n-1)*b_recursive(n-1)+b_recursive(n-2);*/
    int sum=0;
    for(int x=1;x<=n;x++){
        sum+=s_recursive(n,x);
    }
    return sum;
}

int b_dynamic(int n)
{
    int table[n+1][n+1];
    table[0][0]=1;

    for(int i=1;i<=n;i++){
        table[i][0]=table[i-1][i-1];
        for(int j=1;j<=i;j++){
            table[i][j]=table[i-1][j-1]+table[i][j-1];
        }
    }
    return table[n][0];
}


