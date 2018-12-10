#include <iostream>
#include <fstream>
#include <cstring>

#include "BBS.h"
#include "PrimeClass.h"
#include "CoreFunctions.h"
#include "Pollard.h"


void unitTests(){

    std::ifstream gcd_file;
    gcd_file.open("../testFiles/num1_num2_gcd.txt");
    uint64_t num1, num2, gcd_num;
    gcd_file >> num1 >> num2 >> gcd_num;
    bool pass = true;
    while(num1 != 0 || num2 != 0){

        uint64_t temp1;
        uint64_t temp2;
        uint64_t temp =  extendedEuclidianGCD(num1,num2, &temp1, &temp2);
        //int temp = gcd(num1,num2);
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
    uint64_t is_prime;
    is_it_prime_file >> num1 >> is_prime;

    while(num1 != 0){

        bool temp = isPrime(num1,100);
        //int check = temp + is_prime;
        //if((is_prime > check) || (temp > check)){
        if(!temp && is_prime){
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


    uint64_t p;
    uint64_t q;
    uint64_t public_key;
    uint64_t private_key;
    uint64_t z_group;

    /*char message_to_encrypt_char[MAX_LENGTH] = {'\0'};
    uint64_t message_to_encrypt_long[MAX_LENGTH*4] = {0};
    uint64_t message_to_decrypt_long[MAX_LENGTH*4] = {0};
    char decrypted_message_char[MAX_LENGTH] = {'\0'};
    uint64_t decrypted_message_long[MAX_LENGTH*4] = {0};*/

    pass = true;
    std::ifstream pq_file;
    pq_file.open("../testFiles/fullTest.txt");

    pq_file >> p >> q;

    /*while(p != 0){

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
    }*/
    pq_file.close();

    pass = true;
    std::vector<int> prime_list = readFile("../config/primes.txt");

    //uint64_t brute_forced_private_key;
    //uint64_t intercepted_public_key;

    int i = 0;
    while(i < 15){

        srand (time(NULL));

        int first = rand() % prime_list.size();
        int second = rand() % prime_list.size();

        p = prime_list.at(first);
        q = prime_list.at(second);

        //Generate public and private keys from p and q
        //publicKeyGen(p, q, &z_group, &intercepted_public_key);
        //std::cout << "ALICE public key: " << intercepted_public_key << ", " << z_group << std::endl;
        //privateKeyGen(p, q, &z_group, &private_key, intercepted_public_key);
        //std::cout << "ALICE private key: " << private_key << ", " << z_group << std::endl << std::endl;

        //PrimeClass pq = brute_force_exec(z_group);
        uint64_t z_group = p*q;
        uint64_t qq = findP(z_group);
        uint64_t pp = z_group/qq;

        if(pp==q && qq == p){
            uint64_t temp = pp;
            pp = qq;
            qq = temp;

        }

        //privateKeyGen(pp, qq, &z_group, &brute_forced_private_key, intercepted_public_key);

        if(pp != p || qq != q ){
            std::cout << "FACTORING TEST FAILED" << std::endl;
            pass = false;
            break;
        }
        i++;
    }
    if(pass){
        std::cout << "FACTORING TEST SUCCESS" << std::endl;
    }

}

