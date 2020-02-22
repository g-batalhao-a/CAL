/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n)
{
    if(n==0){
        return 1;
    }
    else{
        return factorialRecurs(n-1)*n;
    }

}

int factorialDinam(int n)
{
    int sum=1;
    while(n!=0){
        sum*=n;
        n--;
    }
    return sum;
}
