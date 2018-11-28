#include <iostream>
#include <math.h>

#include "PrimeClass.h"


PrimeClass::PrimeClass( long long int num ) {
    n = num;
    p = 0;
    q = 0;
    n_sqrt = sqrt(n);
}


inline void PrimeClass::findFactor(long long int start) {

    long long int local = n;
    // Unravel loop a bit
    for (long long int i = start; i < n_sqrt; i += 10) {

        if (p != 0 ){
            return;
        }

        if (local % i == 0 ){
            p = i;
            return;
        }
        if (local % (i+2) == 0 ){
            p = i+2;
            return;
        }
        if (local % (i+4) == 0 ){
            p = i+4;
            return;
        }
        if (local % (i+6) == 0 ){
            p = i+6;
            return;
        }
        if (local % (i+8) == 0 ){
            p = i+8;
            return;
        }
    }
}


void PrimeClass::bruteForce(){

    long long int start = 3;

    findFactor(start);

    q = (n / p);

    return;
}
