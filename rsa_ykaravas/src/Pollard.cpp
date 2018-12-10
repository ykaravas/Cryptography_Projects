#include <iostream>
#include <math.h>
#include <cmath>

#include "Pollard.h"


uint64_t PRFactor(uint64_t n, uint64_t x){

    uint64_t a = 2;
    for(int i = 2; i < x; i++){
        uint64_t temp = a;
        for(int j = 0; j < i - 1; j++){
            temp = temp*a;
            temp = temp%n;
        }
        a = temp % n;
    }
    uint64_t d = gcd(a-1,n);
    if((1 < d) && (d  < n)){
        return d;
    }
    else{
        return 0;
    }
}


uint64_t findP(uint64_t n){


    uint64_t x = 2;
    uint64_t d = 0;


    while((x < n) && (d == 0)){
        x +=1;
        d = PRFactor(n,x);
    }

    if(d == 0){
        return 0;
    }
    else{
        return d;
    }
}


