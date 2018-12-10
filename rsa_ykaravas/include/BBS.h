#ifndef BBS_H
#define BBS_H

#include <cstdint>

using namespace std;

class BBS{

public:

    BBS(unsigned int bits);
    unsigned int calcBits(uint64_t num);
    uint64_t generateGroupN(unsigned int bits);
    uint64_t getPrime(unsigned int bits);
    uint64_t next(unsigned int bits);

    uint64_t group_n;
    uint64_t state;
/*
    BBS(long double p, long double q, long double s);

    long double p, q, M, seed, actual;

    long double gcd(long double a, long double b);

    long double getrandom();

    long double getirandom(int i);
    */
};


#endif // BBS_H
