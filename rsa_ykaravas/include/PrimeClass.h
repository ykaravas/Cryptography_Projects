#ifndef PRIMECLASS_H
#define PRIMECLASS_H

#include <cstdint>

class PrimeClass {

public:

    PrimeClass(uint64_t num );

    inline void findFactor(uint64_t start);
    void bruteForce();

    uint64_t get_n() const {return n;}
    uint64_t get_p() const {return p;}
    uint64_t get_q() const {return q;}
    uint64_t get_sqrt_n() const {return n_sqrt;}

    uint64_t n;
    uint64_t p;
    uint64_t q;
    uint64_t n_sqrt;
};
#endif
