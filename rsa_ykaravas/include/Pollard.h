#ifndef POLLARD_H
#define POLLARD_H

#include<cstdint>

#include <CoreFunctions.h>


uint64_t PRFactor(uint64_t n, uint64_t x);
uint64_t findP(uint64_t n);


#endif // POLLARD_H
