#ifndef COREFUNCTIONS_H
#define COREFUNCTIONS_H

#include <vector>
#include <string>
#include <cstdint>

#include "PrimeClass.h"


//uint64_t prime(uint64_t is_prime);
uint64_t extendedEuclidianGCD(uint64_t num1, uint64_t num2, uint64_t *temp1, uint64_t *temp2);
uint64_t gcd(uint64_t p, uint64_t q);
uint64_t fastExponentiation(uint64_t base, uint64_t exponent, uint64_t modulo);
uint64_t publicKeyGen(uint64_t p, uint64_t q, uint64_t *modulo, uint64_t *exponent);
uint64_t privateKeyGen(uint64_t p, uint64_t q, uint64_t *modulo, uint64_t *exponent, uint64_t pub);
int encrypt(uint64_t* in, uint64_t exponent, uint64_t modulo, uint64_t* encrypted_msg_segment, size_t len);
int decrypt(uint64_t* in, uint64_t exponent, uint64_t modulo, uint64_t* decrypted_msg_segment, size_t len);
PrimeClass brute_force_exec(uint64_t group);
std::vector<int> readFile(std::string filename);
bool isPrime(uint64_t n, uint64_t k);
bool millerRabin(uint64_t d, uint64_t n);
uint64_t powr(uint64_t x, uint64_t y, uint64_t p);


// Helper functions

int convertChar2Long(char* char_in, uint64_t* long_out, bool rand_in);
int convertLong2Char(uint64_t* long_in, char* char_out, bool sub);

#endif // COREFUNCTIONS_H
