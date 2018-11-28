#include <math.h>
#include <iostream>
#include <limits.h>

#include "CoreFunctions.h"


PrimeClass brute_force_exec(long long int group) {

    PrimeClass test(group);

    test.bruteForce();

    std::cout << "p: " << test.p << std::endl;
    std::cout << "q: " << test.q << std::endl;
    return test;
}


long long int prime(long long int is_prime) {

    long long int temp = sqrt(is_prime);
    for (long long int i = 2; i < temp; i++) {

        if ((is_prime % i) == 0) {

            return i;
        }
    }
    return 0;
}


// modulo = (p-1)*(q-1)
// The exponent is coprime to modulo
long long int publicKeyGen(long long int p, long long int q, long long int *modulo, long long int *exponent) {

    *modulo = (p-1)*(q-1);

    *exponent = (long long int)sqrt(*modulo);

    // Find a coprime
    while (gcd(*exponent, *modulo) != 1) {

        (*exponent)++;
    }

    *modulo = p*q;
    return 0;
}


// exponent is, x, such that (x*pub) % modulo = 1
long long int privateKeyGen(long long int p, long long int q, long long int *modulo, long long int *exponent, long long int pub) {

    *exponent = 1;
    *modulo = (p-1)*(q-1);
    long long int temp = pub;

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
int encrypt(long long int* in, long long int exponent, long long int modulo, long long int* encrypted_msg_segment, size_t len) {

    // Parallelize a bit here for speedup
    #pragma omp parallel for
    for (unsigned int i = 0; i < len; i++) {

        long long int msg_segment = in[i];
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
int decrypt(long long int* in, long long int exponent, long long int modulo, long long int* decrypted_msg_segment, size_t len) {


    #pragma omp parallel for
    for (unsigned int i=0; i < len; i++)
    {
        long long int encrypted_msg_segment = in[i];
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


long long int fastExponentiation(long long int base, long long int exponent, long long int modulo) {

   long long int out = 1;

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


int convertChar2Long(char* char_in, long long int* long_out, bool rand_in) {

   while(*char_in != '\0') {

      long long int r = 0;

      if (rand_in) {

         r = (rand()%INT_MAX) - (INT_MAX/2);
         *long_out++ = r;
      }
      *long_out++ = (long long int)(*char_in++) + r;
   }

   *long_out++ = 0;
   *long_out = 0;
   return 0;
}


int convertLong2Char(long long int* long_in, char* char_out, bool sub) {

   while((*(long_in+1) != 0) || (*long_in != 0)) {

      long long int r = 0;
      if (sub) {

         r = *long_in++;
      }
      *char_out++ = (char)(*long_in++) - r;
   }
   *char_out = '\0';
   return 0;
}


long long int gcd(long long int p, long long int q) {

   if(p < q) {

       long long int temp=p;
       p=q;
       q=temp;
   }

   while(q != 0) {

      long long int tmp = q;
      q = p%q;
      p = tmp;
   }

   return p;
}


