#include <iostream>
#include <fstream>
#include <cstring>

#include "PrimeClass.h"
#include "CoreFunctions.h"


void unitTests(){

    std::ifstream gcd_file;
    gcd_file.open("../testFiles/num1_num2_gcd.txt");
    long long int num1, num2, gcd_num;
    gcd_file >> num1 >> num2 >> gcd_num;
    bool pass = true;
    while(num1 != 0 || num2 != 0){

        int temp = gcd(num1,num2);
        if(temp != gcd_num){
            std::cout << "GCD UNIT TEST FAILED" << std::endl;
            pass = false;
        }
        gcd_file >> num1 >> num2 >> gcd_num;
    }
    if(pass){
        std::cout << "GCD UNIT TEST SUCCESS" << std::endl;
    }
    gcd_file.close();


    pass = true;
    std::ifstream is_it_prime_file;
    is_it_prime_file.open("../testFiles/num_isitprime.txt");
    long long int is_prime;
    is_it_prime_file >> num1 >> is_prime;

    while(num1 != 0){

        int temp = prime(num1);
        int check = temp + is_prime;
        if((is_prime > check) || (temp > check)){
            std::cout << "PRIME UNIT TEST FAILED" << std::endl;
            pass = false;
        }
        is_it_prime_file >> num1 >> is_prime;
    }
    if(pass){
        std::cout << "PRIME UNIT TEST SUCCESS" << std::endl;
    }

    is_it_prime_file.close();

#define MAX_LENGTH 10000


    long long int p;
    long long int q;
    long long int public_key;
    long long int private_key;
    long long int z_group;

    char message_to_encrypt_char[MAX_LENGTH];
    long long int message_to_encrypt_long[MAX_LENGTH*4];
    long long int message_to_decrypt_long[MAX_LENGTH*4];
    char decrypted_message_char[MAX_LENGTH];
    long long int decrypted_message_long[MAX_LENGTH*4];

    pass = true;
    std::ifstream pq_file;
    pq_file.open("../testFiles/fullTest.txt");

    pq_file >> p >> q;

    while(p != 0){

        publicKeyGen(p, q, &z_group, &public_key);
        //std::cout << "public key: " << public_key << ", " << z_group << std::endl;
        privateKeyGen(p, q, &z_group, &private_key, public_key);
        //std::cout << "private key: " << private_key << ", " << z_group << std::endl;


        std::istream* mesgFile;
        mesgFile = new std::ifstream("../config/msg.txt");

        mesgFile->getline(message_to_encrypt_char, MAX_LENGTH);
        unsigned int len = strlen(message_to_encrypt_char);


        //Encrypt, then decrypt the message
        //std::cout << "Original text: " << message_to_encrypt_char << std::endl;
        convertChar2Long(message_to_encrypt_char, message_to_encrypt_long,true);

        encrypt(message_to_encrypt_long, public_key, z_group, message_to_decrypt_long, len*4);

        decrypt(message_to_decrypt_long, private_key, z_group, decrypted_message_long, MAX_LENGTH*4);

        convertLong2Char(decrypted_message_long, decrypted_message_char,true);

        std::string orig_message(message_to_encrypt_char);
        std::string dec_message(decrypted_message_char);
        int comparison = orig_message.compare(dec_message);

        if(comparison){
            std::cout << "FULL TEST FAILED" << std::endl;
            pass = false;
            break;
        }
        pq_file >> p >> q;
    }
    if(pass){
        std::cout << "FULL TEST SUCCESS" << std::endl;
    }


    pass = true;
    std::vector<int> prime_list = readFile("../config/primes.txt");

    long long int brute_forced_private_key;
    long long int intercepted_public_key;

    int i = 0;
    while(i < 15){

        srand (time(NULL));

        int first = rand() % prime_list.size();
        int second = rand() % prime_list.size();

        p = prime_list.at(first);
        q = prime_list.at(second);

        //Generate public and private keys from p and q
        publicKeyGen(p, q, &z_group, &intercepted_public_key);
        //std::cout << "ALICE public key: " << intercepted_public_key << ", " << z_group << std::endl;
        privateKeyGen(p, q, &z_group, &private_key, intercepted_public_key);
        //std::cout << "ALICE private key: " << private_key << ", " << z_group << std::endl << std::endl;

        PrimeClass pq = brute_force_exec(z_group);
        privateKeyGen(pq.p, pq.q, &z_group, &brute_forced_private_key, intercepted_public_key);

        if(brute_forced_private_key != private_key){
            std::cout << "FULL TEST FAILED" << std::endl;
            pass = false;
            break;
        }
    }
    if(pass){
        std::cout << "FACTORING TEST SUCCESS" << std::endl;
    }
    /*
    prime(long long int is_prime); // (num is_prime?)
    gcd(long long int p, long long int q); // (num1 num2 gcdnum)
    fastExponentiation(long long int base, long long int exponent, long long int modulo); // (prime1 prime2, n)
    publicKeyGen(long long int p, long long int q, long long int *modulo, long long int *exponent); // (p q pub_key)
    privateKeyGen(long long int p, long long int q, long long int *modulo, long long int *exponent, long long int pub); // (p q pub_key priv_key)
    encrypt(long long int* in, long long int exponent, long long int modulo, long long int* encrypted_msg_segment, size_t len); // (msg hash)
    decrypt(long long int* in, long long int exponent, long long int modulo, long long int* decrypted_msg_segment, size_t len); // (hash msg)
    brute_force_exec(long long int group); // (prime1 prime2, n)
    */

}

// (prime1 prime2, n)
// (num is_prime?)
// (num1 num2 gcdnum)
// (p q pub_key priv_key)
// (msg hash)
