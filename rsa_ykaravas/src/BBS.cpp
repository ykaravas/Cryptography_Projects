#include <iostream>
#include <cmath>
#include <math.h>
#include <random>
#include <time.h>

#include "CoreFunctions.h"
#include "BBS.h"

using namespace std;


BBS::BBS(unsigned int bits){

    group_n = generateGroupN(bits);

    srand (time(NULL));
    uint64_t min = 2;
    uint64_t max = 2;
    for(unsigned int i = 0; i< (bits - 2); i++){
        min *= 2;
    }

    for(unsigned int i = 0; i < (bits - 1); i++){
        max *= 2;
    }
    max = max - 2;

    uint64_t seed = min + rand() % (( max + 1 ) - min);
    state = seed % group_n;
}


uint64_t BBS::getPrime(unsigned int bits){

    uint64_t possible_prime = 0;
    uint64_t min = 2;
    uint64_t max = 2;

    for(unsigned int i = 0; i< ((bits - 2)/2); i++){
        min *= 2;
    }

    srand (time(NULL));

    //if (bits == 0){
    max = group_n - 2;
    possible_prime = min + rand() % ( max - min);

    bool cont = true;
    while(cont){
        bool primality = isPrime(possible_prime, 100);
        if(primality){
            bool primality2 = (possible_prime % 4) == 3;
            if(primality2){
                cont = false;
                return possible_prime;
            }
            else{
                possible_prime++;
            }
        }
        else{
            possible_prime++;
        }
    }
}


uint64_t BBS::generateGroupN(unsigned int bits){

    int new_bits = bits/2;
    uint64_t p = getPrime(new_bits);
    while(1){
        uint64_t q = getPrime(new_bits);
        if(p != q){
            return p * q;
        }
    }
}


unsigned int BBS::calcBits(uint64_t n){

   unsigned int count = 0;
   while (n)
   {
        count++;
        n >>= 1;
    }
    return count;
}


uint64_t BBS::next(unsigned int bits){

    uint64_t possible_prime = 0;
    int new_bits = bits/2;

    while(true){
        possible_prime = 0;
        for(unsigned int i = 0; i < new_bits; i++){

            uint64_t temp = state*state;
            state = (temp % group_n);

            possible_prime = (possible_prime << 1) | (state & 1);
        }

        bool primality = isPrime(possible_prime, 100);
        bool primality2 = (possible_prime % 4) == 3;
        if(primality && primality2){
            return possible_prime;
        }
    }
}
