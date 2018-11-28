#ifndef COREFUNCTIONS_H
#define COREFUNCTIONS_H

#include "PrimeClass.h"




long long int prime(long long int is_prime);
long long int gcd(long long int p, long long int q);
long long int fastExponentiation(long long int base, long long int exponent, long long int modulo);
long long int publicKeyGen(long long int p, long long int q, long long int *modulo, long long int *exponent);
long long int privateKeyGen(long long int p, long long int q, long long int *modulo, long long int *exponent, long long int pub);
int encrypt(long long int* in, long long int exponent, long long int modulo, long long int* encrypted_msg_segment, size_t len);
int decrypt(long long int* in, long long int exponent, long long int modulo, long long int* decrypted_msg_segment, size_t len);
PrimeClass brute_force_exec(long long int group);


// Helper functions

int convertChar2Long(char* char_in, long long int* long_out, bool rand_in);
int convertLong2Char(long long int* long_in, char* char_out, bool sub);

#endif // COREFUNCTIONS_H
