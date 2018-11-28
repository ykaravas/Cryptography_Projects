#ifndef PRIMECLASS_H
#define PRIMECLASS_H


class PrimeClass {

public:

    PrimeClass(long long int num );

    inline void findFactor(long long int start);
    void bruteForce();

    long long int get_n() const {return n;}
    long long int get_p() const {return p;}
    long long int get_q() const {return q;}
    long long int get_sqrt_n() const {return n_sqrt;}

    long long int n;
    long long int p;
    long long int q;
    long long int n_sqrt;
};
#endif
