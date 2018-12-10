#include <math.h>
#include <iostream>
#include <limits.h>
#include <sstream>
#include <fstream>
#include <bits/stdc++.h>


#include "CoreFunctions.h"



std::vector<int> readFile(std::string filename){

    std::ifstream data(filename);
    std::string line;
    std::vector<int> prime_list;

    while (std::getline(data, line)){

        std::stringstream lineStream(line);

        std::string cell;
        while(std::getline(lineStream, cell, ',')){

            prime_list.push_back(std::stoll(cell));
        }
    }
    return prime_list;
}


PrimeClass brute_force_exec(uint64_t group) {

    PrimeClass test(group);

    test.bruteForce();

    std::cout << "p: " << test.p << std::endl;
    std::cout << "q: " << test.q << std::endl;
    return test;
}


/*uint64_t prime(uint64_t is_prime) {

    uint64_t temp = sqrt(is_prime);
    for (uint64_t i = 2; i < temp; i++) {

        if ((is_prime % i) == 0) {

            return i;
        }
    }
    return 0;
}*/


// modulo = (p-1)*(q-1)
// The exponent is coprime to modulo
uint64_t publicKeyGen(uint64_t p, uint64_t q, uint64_t *modulo, uint64_t *exponent) {

    *modulo = (p-1)*(q-1);

    *exponent = (uint64_t)sqrt(*modulo);

    // Find a coprime
    while (gcd(*exponent, *modulo) != 1) {

        (*exponent)++;
    }

    *modulo = p*q;
    return 0;
}


// exponent is, x, such that (x*pub) % modulo = 1
uint64_t privateKeyGen(uint64_t p, uint64_t q, uint64_t *modulo, uint64_t *exponent, uint64_t pub) {

    *exponent = 1;
    *modulo = (p-1)*(q-1);
    uint64_t temp = pub;

    while((temp%(*modulo)) != 1) {

        temp += pub;
        temp %= *modulo; // (a*b)%c = ((a%c)*b)%c
        (*exponent)++;
    }

    *modulo = p*q;
    return 0;
}




// exp and mod = pub key
// encrypted: encrypted_message_segment = (msg_segment^exponent)%modulo
int encrypt(uint64_t* in, uint64_t exponent, uint64_t modulo, uint64_t* encrypted_msg_segment, size_t len) {

    // Parallelize a bit here for speedup
    #pragma omp parallel for
    for (unsigned int i = 0; i < len; i++) {

        uint64_t msg_segment = in[i];
        #if 1
            encrypted_msg_segment[i] = fastExponentiation(msg_segment, exponent, modulo);
        #else
            for (int j = 1; j < exponent; j++) {
                msg_segment *= in[j];
                msg_segment %= modulo;
            }

            encrypted_msg_segment[i] = msg_segment;
        #endif
    }

    encrypted_msg_segment[len]='\0';

    return 0;
}


// exp and mod = priv key
// decrypted: decrypted_msg_segment = (encrypted_msg_segment^exponent)%modulo
int decrypt(uint64_t* in, uint64_t exponent, uint64_t modulo, uint64_t* decrypted_msg_segment, size_t len) {


    #pragma omp parallel for
    for (unsigned int i=0; i < len; i++)
    {
        uint64_t encrypted_msg_segment = in[i];
        #if 1
            decrypted_msg_segment[i] = fastExponentiation(encrypted_msg_segment, exponent, modulo);
        #else
            for (int j = 1; j < exponent; j++) {

                encrypted_msg_segment *= in[j];
                encrypted_msg_segment %= modulo;
            }

            decrypted_msg_segment[i] = encrypted_msg_segment;
        #endif
    }

    decrypted_msg_segment[len]='\0';

    return 0;
}


uint64_t fastExponentiation(uint64_t base, uint64_t exponent, uint64_t modulo) {

   uint64_t out = 1;

   while(exponent > 0) {

      if((exponent%2) == 1) {

         out*=base;
         out%=modulo;
      }

      base = base * base;
      base %= modulo;
      exponent /= 2;
   }

   return out;
}


int convertChar2Long(char* char_in, uint64_t* long_out, bool rand_in) {

   while(*char_in != '\0') {

      uint64_t r = 0;

      if (rand_in) {

         r = (rand()%INT_MAX) - (INT_MAX/2);
         *long_out++ = r;
      }
      *long_out++ = (uint64_t)(*char_in++) + r;
   }

   *long_out++ = 0;
   *long_out = 0;
   return 0;
}


int convertLong2Char(uint64_t* long_in, char* char_out, bool sub) {

   while((*(long_in+1) != 0) || (*long_in != 0)) {

      uint64_t r = 0;
      if (sub) {

         r = *long_in++;
      }
      *char_out++ = (char)(*long_in++) - r;
   }
   *char_out = '\0';
   return 0;
}


uint64_t gcd(uint64_t p, uint64_t q) {

   if(p < q) {

       uint64_t temp=p;
       p=q;
       q=temp;
   }

   while(q != 0) {

      uint64_t tmp = q;
      q = p%q;
      p = tmp;
   }

   return p;
}







// Utility function to do modular exponentiation.
// It returns (x^y) % p
uint64_t power(uint64_t x, uint64_t y, uint64_t p){

    uint64_t res = 1;	 // Initialize result
    x = x % p; // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1){
            res = (res*x) % p;
        }

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

// This function is called for all k trials. It returns
// false if n is composite and returns false if n is
// probably prime.
// d is an odd number such that d*2<sup>r</sup> = n-1
// for some r >= 1
bool millerTest(uint64_t d, uint64_t n)
{
    // Pick a random number in [2..n-2]
    // Corner cases make sure that n > 4
    uint64_t a = 2 + rand() % (n - 4);

    // Compute a^d % n
    uint64_t x = power(a, d, n);

    if (x == 1 || x == n-1){
        return true;
    }

    // Keep squaring x while one of the following doesn't
    // happen
    // (i) d does not reach n-1
    // (ii) (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n-1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1){
            return false;
        }
        if (x == n-1){
            return true;
        }
    }

    // Return composite
    return false;
}

// It returns false if n is composite and returns true if n
// is probably prime. k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
bool isPrime(uint64_t n, uint64_t k)
{
    // Corner cases
    if (n <= 1 || n == 4){

        return false;
    }
    if (n <= 3){

        return true;
    }

    // Find r such that n = 2^d * r + 1 for some r >= 1
    uint64_t d = n - 1;
    while (d % 2 == 0){
        d /= 2;
    }

    // Iterate given nber of 'k' times
    for (unsigned int i = 0; i < k; i++){
        if (!millerTest(d, n)){
            return false;
        }
    }

    return true;
}

// Driver program
/*int main()
{
    int k = 4; // Number of iterations

    cout << "All primes smaller than 100: \n";
    for (int n = 1; n < 100; n++)
    if (isPrime(n, k))
        cout << n << " ";

    return 0;
}*/

