#include <iostream>
#include <fstream>
#include <limits.h>
#include <string.h>
#include <time.h>

#include "BBS.h"
#include "CoreFunctions.h"
#include "unittests.h"


#define MAX_LENGTH 10000


int main() {


    while(1) {

        uint64_t bob_public_key;
        uint64_t bob_private_key;
        uint64_t bob_z_group;
        uint64_t alice_public_key;
        uint64_t alice_private_key;
        uint64_t alice_z_group;
        uint64_t brute_forced_private_key;

        char message_to_encrypt_char[MAX_LENGTH] = {'\0'};
        uint64_t message_to_encrypt_long[MAX_LENGTH*4] = {0};
        char message_to_decrypt_char[MAX_LENGTH] = {'\0'};
        uint64_t message_to_decrypt_long[MAX_LENGTH*4] = {0};
        char decrypted_message_char[MAX_LENGTH] = {'\0'};
        uint64_t decrypted_message_long[MAX_LENGTH*4] = {0};
        std::cout << std::endl;
        std::cout << "             MAIN PROGRAM FUNCTIONALITY & COMMAND LINE OPTIONS                  " << std::endl;
        std::cout << "------------------------------------------------------------------------------" << std::endl;
        std::cout << "       'gen'          to generate key pairs for BOB and ALICE" <<std::endl;
        std::cout << "       'enc'          to encrypt message located in 'config/msg.txt'" <<std::endl;
        std::cout << "       'dec'          to decrypt message located in 'output/Alice/enc_msg.dat'" << std::endl;
        std::cout << "       'eve'          to intercept ALICE message and BOB public key and find p & q" << std::endl;
        std::cout << "       'msg'          to change message content in 'config/msg.txt' file." << std::endl;
        std::cout << "      'unit'          to run all unit tests" << std::endl;
        std::cout << "      'exit'          to end/exit program" << std::endl << std::endl << std::endl;
        std::cout << "                          AUXILIARY FUNCTIONS" << std::endl;
        std::cout << "------------------------------------------------------------------------------" << std::endl;
        std::cout << "    'factor'          to factor a number into two primes (if possible)" << std::endl;
        std::cout << "       'gcd'          to find gcd of two numbers" << std::endl;
        std::cout << "     'prime'          to find if a number is prime or not" << std::endl;
        std::cout << "    'modexp'          to perform fast exponentiation" << std::endl << std::endl << std::endl;

        std::cout << "Enter Desired Opertation: ";

        std::string input;
        std::cin >> input;

        if(input == "gen"){

            std::cout << "\nType c to use Config file or r for random primes from primes.txt \n or b for BlumBlumShub: ";


            std::string input2;
            std::cin >> input2;
            std::cout << std::endl;
            std::pair<int, int> alice_primes;
            std::pair<int, int> bob_primes;

            if(input2 == "c" || input2 == "C"){
                std::ifstream genfile;
                genfile.open("../config/gen.txt");

                genfile >> bob_primes.first >> bob_primes.second;
                genfile >> alice_primes.first >> alice_primes.second;

                if((bob_primes.first == 0) || (bob_primes.second == 0)) {
                    std::cout << std::endl << std::endl
                              << "Generator file with p and q, 'gen.txt', does not exist."
                              << std::endl << std::endl;
                    continue;
                }

            }
            else if(input2 == "r" || input2 == "R"){

                std::vector<int> prime_list = readFile("../config/primes.txt");


                srand (time(NULL));

                int first = rand() % prime_list.size();
                int second = rand() % prime_list.size();

                bob_primes.first = prime_list.at(first);
                bob_primes.second = prime_list.at(second);

                std::cout << "BOB Primes are P = " << bob_primes.first << " and Q = " << bob_primes.second << std::endl << std::endl;

                first = rand() % prime_list.size();
                second = rand() % prime_list.size();

                alice_primes.first = prime_list.at(first);
                alice_primes.second = prime_list.at(second);

                std::cout << "ALICE Primes are P = " << alice_primes.first << " and Q = " << alice_primes.second << std::endl << std::endl;

            }

            else if(input2 == "b" || input2 == "B"){

                std::cout << "Enter Number if Bits Desired: ";

                std::string input;
                std::cin >> input;

                unsigned int bits = std::stoi(input);

                BBS bbs_bob = BBS(bits);

                bob_primes.first =  bbs_bob.next(bits);
                bob_primes.second =  bbs_bob.next(bits);

                std::cout << "BOB Primes are P = " << bob_primes.first << " and Q = " << bob_primes.second << std::endl << std::endl;

                BBS bbs_alice = BBS(bits);
                alice_primes.first =  bbs_alice.next(bits);
                alice_primes.second =  bbs_alice.next(bits);

                std::cout << "ALICE Primes are P = " << alice_primes.first << " and Q = " << alice_primes.second << std::endl << std::endl;

            }

            if (!(isPrime(alice_primes.first,100) || isPrime(alice_primes.first,100))) {

                std::cerr << "ALICE primes are invalid." << std::endl;
                return 1;
            }
            if (!(isPrime(bob_primes.first,100) || isPrime(bob_primes.first,100))) {

                std::cerr << "BOB primes are invalid." << std::endl;
                return 1;
            }


            //Generate public and private keys from p and q
            publicKeyGen(alice_primes.first, alice_primes.second, &alice_z_group, &alice_public_key);
            std::cout << "ALICE public key: " << alice_public_key << ", " << alice_z_group << std::endl;
            privateKeyGen(alice_primes.first, alice_primes.second, &alice_z_group, &alice_private_key, alice_public_key);
            std::cout << "ALICE private key: " << alice_private_key << ", " << alice_z_group << std::endl << std::endl;

            std::ofstream alice_pub_key_file;
            alice_pub_key_file.open("../output/Alice/pub_key.txt");
            alice_pub_key_file << alice_public_key << " " << alice_z_group << "\n";
            alice_pub_key_file.close();


            std::ofstream alice_priv_key_file;
            alice_priv_key_file.open("../output/Alice/priv_key.txt");
            alice_priv_key_file << alice_private_key << " " << alice_z_group << "\n";
            alice_priv_key_file.close();

            //Generate public and private keys from p and q
            publicKeyGen(bob_primes.first, bob_primes.second, &bob_z_group, &bob_public_key);
            std::cout << "BOB public key: " << bob_public_key << ", " << bob_z_group << std::endl;
            privateKeyGen(bob_primes.first, bob_primes.second, &bob_z_group, &bob_private_key, bob_public_key);
            std::cout << "BOB private key: " << bob_private_key << ", " << bob_z_group << std::endl << std::endl;

            std::ofstream bob_pub_key_file;
            bob_pub_key_file.open("../output/Bob/pub_key.txt");
            bob_pub_key_file << bob_public_key << " " << bob_z_group << "\n";
            bob_pub_key_file.close();


            std::ofstream bob_priv_key_file;
            bob_priv_key_file.open("../output/Bob/priv_key.txt");
            bob_priv_key_file << bob_private_key << " " << bob_z_group << "\n";
            bob_priv_key_file.close();

        }

        else if(input == "enc"){

            std::istream* mesgFile;
            mesgFile = new std::ifstream("../config/msg.txt");

            mesgFile->getline(message_to_encrypt_char, MAX_LENGTH);
            unsigned int len = strlen(message_to_encrypt_char);

            //Encrypt, then decrypt the message
            std::cout << "ALICE Original message: " << message_to_encrypt_char << std::endl;
            convertChar2Long(message_to_encrypt_char, message_to_encrypt_long,false);


            //Encrypt
            std::ifstream pubkey;
            pubkey.open("../output/Bob/pub_key.txt");
            uint64_t key;
            uint64_t group;
            pubkey >> key >> group;

            if(key == 0){
                std::cout << std::endl << std::endl
                          << "Public key file, 'Bob/pub_key.txt', does not exist."
                          << std::endl << std::endl;
                continue;
            }

            encrypt(message_to_encrypt_long, key, group, message_to_decrypt_long, len*4);
            convertLong2Char(message_to_decrypt_long, message_to_decrypt_char,false);
            std::cout << "ALICE Encrypted message to BOB: " << message_to_decrypt_char << std::endl;
            std::ofstream enc_msg_txt;


            enc_msg_txt.open("../output/Alice/enc_msg.dat",std::ios::binary);
            for(int i = 0; i < int(sizeof(message_to_decrypt_long)/sizeof(message_to_decrypt_long[0])); i++){
                enc_msg_txt << message_to_decrypt_long[i] << "\n";
            }
            pubkey.close();
            enc_msg_txt.close();

        }

        else if (input == "dec"){

            std::ifstream encMesgFile;

            encMesgFile.open("../output/Alice/enc_msg.dat", std::ios::binary);
            for(int i = 0; i < int(sizeof(message_to_decrypt_long)/sizeof(message_to_decrypt_long[0])); i++){
                encMesgFile >> message_to_decrypt_long[i];
            }

            encMesgFile.close();
            //Decrypt

            std::ifstream privkey;
            privkey.open("../output/Bob/priv_key.txt");
            uint64_t key;
            uint64_t group;
            privkey >> key >> group;

            if(key == 0) {
                std::cout << std::endl << std::endl
                          << "Private key file, 'Bob/priv_key.txt', does not exist."
                          << std::endl << std::endl;
                continue;
            }

            decrypt(message_to_decrypt_long, key, group, decrypted_message_long, MAX_LENGTH*4);

            convertLong2Char(decrypted_message_long, decrypted_message_char,false);
            std::cout << "BOB Decrypted ALICE message: " << decrypted_message_char << std::endl;
            std::ofstream dec_msg_txt;
            dec_msg_txt.open("../output/Bob/dec_msg.txt");
            dec_msg_txt << decrypted_message_char;
            dec_msg_txt.close();
        }
        else if (input == "eve"){

            std::ifstream pubkey;
            pubkey.open("../output/Bob/pub_key.txt");
            uint64_t intercepted_pub_key;
            uint64_t group;
            pubkey >> intercepted_pub_key >> group;
            if((intercepted_pub_key == 0) && (group == 0)){
                std::cout << std::endl << std::endl
                          << "Intercepted public key file, 'Bob/pub_key.txt', does not exist."
                          << std::endl << std::endl;
                continue;
            }
            PrimeClass pq = brute_force_exec(group);
            privateKeyGen(pq.p, pq.q, &group, &brute_forced_private_key, intercepted_pub_key);
            std::cout << "EVE Brute Forced BOB Private key: " << brute_forced_private_key << std::endl;
            // Decrypt Alice's message
            std::ifstream encMesgFile;

            encMesgFile.open("../output/Alice/enc_msg.dat", std::ios::binary);
            for(int i = 0; i < int(sizeof(message_to_decrypt_long)/sizeof(message_to_decrypt_long[0])); i++){
                encMesgFile >> message_to_decrypt_long[i];
            }

            encMesgFile.close();
            decrypt(message_to_decrypt_long, brute_forced_private_key, group, decrypted_message_long, MAX_LENGTH*4);

            convertLong2Char(decrypted_message_long, decrypted_message_char,false);
            std::cout << "EVE Decrypted ALICE message to BOB: " << decrypted_message_char << std::endl;
            std::ofstream dec_msg_txt;
            dec_msg_txt.open("../output/Eve/intercepted_msg.txt");
            dec_msg_txt << decrypted_message_char;
            dec_msg_txt.close();

            // Save Brute Forced key
            std::ofstream brute_forced_key_file;
            brute_forced_key_file.open("../output/Eve/brute_forced_priv_key.txt");
            brute_forced_key_file << brute_forced_private_key << " " << group << "\n";
            brute_forced_key_file.close();
            pubkey.close();

        }
        else if (input == "unit") {

            unitTests();
        }
        else if (input == "factor") {

            std::cout << "\nEnter a pq to be factored: ";
            std::string num1;
            std::cin >> num1;
            std::cout << std::endl;

            uint64_t num2;
            num2 = std::stoll(num1);
            PrimeClass pq = brute_force_exec(num2);

            std::cout << "Prime factors of " << num2 << " are " << pq.p << " and " << pq.q << std::endl << std::endl;

        }
        else if (input == "gcd") {

            std::cout << "\nEnter two numbers to find their gcd: ";
            std::string num1, num2;
            std::cin >> num1;
            std::cin >> num2;
            std::cout << std::endl;

            uint64_t num3, num4;
            num3 = std::stoll(num1);
            num4 = std::stoll(num2);

            uint64_t denominator = gcd(num3,num4);

            std::cout << "GCD of " << num3 << " and " << num4 << " is " << denominator << std::endl << std::endl;

        }
        else if (input == "prime") {

            std::cout << "\nEnter a number to find if it is prime or not: ";
            std::string num1;
            std::cin >> num1;
            std::cout << std::endl;

            uint64_t num2;
            num2 = std::stoll(num1);

            uint64_t is_prime = isPrime(num2,100);

            if(is_prime == 0){

                std::cout <<  num2 << " is prime."  << std::endl << std::endl;
            }
            else{
                std::cout <<  num2 << " is not prime."  << std::endl << std::endl;

            }
        }
        else if (input == "modexp") {

            std::cout << "\nEnter three numbers, base, exponent and modulo to perform Fast Exp: ";
            std::string num1, num2, num3;
            std::cin >> num1;
            std::cin >> num2;
            std::cin >> num3;
            std::cout << std::endl;

            uint64_t num4, num5, num6;
            num4 = std::stoll(num1);
            num5 = std::stoll(num2);
            num6 = std::stoll(num3);

            uint64_t out = fastExponentiation(num4,num5, num6);

            std::cout << "Fast Exponentiation output of Base: " << num4 << ",  Exponent: " << num5
                      << ",  Modulo: " << num6 << " is " << out << std::endl << std::endl;

        }
        else if (input == "msg"){

            std::cout << "\nEnter new message for the 'config/msg.txt' file: ";
            std::string new_msg;
            std::cin >> new_msg;

            std::ofstream msg_txt;
            msg_txt.open("../config/msg.txt");
            msg_txt << new_msg;
            msg_txt.close();

        }
        else if (input == "exit") {

            return 0;
        }
        else {
            std::cout << "Invalid Input. Try again." << std::endl;
        }
    }
}

