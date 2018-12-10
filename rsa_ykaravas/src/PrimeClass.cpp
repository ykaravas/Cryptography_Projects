#include <iostream>
#include <math.h>

#include "PrimeClass.h"


PrimeClass::PrimeClass( uint64_t num ) {
    n = num;
    p = 0;
    q = 0;
    n_sqrt = sqrt(n);
}


inline void PrimeClass::findFactor(uint64_t start) {

    uint64_t local = n;
    // Unravel loop a bit
    for (uint64_t i = start; i < n_sqrt; i += 10) {

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

    uint64_t start = 3;

    findFactor(start);

    q = (n / p);

    return;
}
