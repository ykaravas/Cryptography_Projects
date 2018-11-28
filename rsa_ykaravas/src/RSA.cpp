#include <math.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <string.h>
#include <cstring>

#include "CoreFunctions.h"
#include "unittests.h"


#define MAX_LENGTH 10000



int main() {


    while(1) {
        long long int p;
        long long int q;
        long long int public_key;
        long long int private_key;
        long long int z_group;

        char message_to_encrypt_char[MAX_LENGTH] = {'\0'};
        long long int message_to_encrypt_long[MAX_LENGTH*4] = {0};
        char message_to_decrypt_char[MAX_LENGTH] = {'\0'};
        long long int message_to_decrypt_long[MAX_LENGTH*4] = {0};
        char decrypted_message_char[MAX_LENGTH] = {'\0'};
        long long int decrypted_message_long[MAX_LENGTH*4] = {0};
        std::cout << std::endl;
        std::cout << "------------------------------------------------------------------------------" << std::endl;
        std::cout << "Operation Choices: 'gen' to generate key pairs" <<std::endl;
        std::cout << "                   'enc' to encrypt message located in msg.txt" <<std::endl;
        std::cout << "                   'dec' to decrypt message located in enc_msg.dat" << std::endl;
        std::cout << "                   'eve' to intercept message with public key and find p & q" << std::endl;
        std::cout << "                   'unit' to run unit tests" << std::endl;
        std::cout << "                   'exit' to end program" << std::endl << std::endl << std::endl;

        std::cout << "Enter Desired Opertation: ";


        std::string input;
        std::cin >> input;

        if(input == "gen"){
            std::ifstream genfile;
            genfile.open("../config/gen.txt");

            genfile >> p >> q;

            if((p == 0) || (q == 0)) {
                std::cout << std::endl << std::endl
                          << "Generator file with p and q, 'gen.txt', does not exist."
                          << std::endl << std::endl;
                continue;
            }

            if (prime(p)) {

                std::cerr << p << " is not prime." << std::endl;
                return 1;
            }
            if (prime(q)) {

                std::cerr << q << " is not prime." << std::endl;
                return 1;
            }


            //Generate public and private keys from p and q
            publicKeyGen(p, q, &z_group, &public_key);
            std::cout << "public key: " << public_key << ", " << z_group << std::endl;
            privateKeyGen(p, q, &z_group, &private_key, public_key);
            std::cout << "private key: " << private_key << ", " << z_group << std::endl;

            std::ofstream pub_key_file;
            pub_key_file.open("../output/my_pub_key.txt");
            pub_key_file << public_key << " " << z_group << "\n";
            pub_key_file.close();

            // Generate default public key to intercept as well
            std::ofstream other_pub_key_file;
            other_pub_key_file.open("../output/other_pub_key.txt");
            other_pub_key_file << public_key << " " << z_group << "\n";
            other_pub_key_file.close();

            std::ofstream priv_key_file;
            priv_key_file.open("../output/my_priv_key.txt");
            priv_key_file << private_key << " " << z_group << "\n";
            priv_key_file.close();

        }

        else if(input == "enc"){

            std::istream* mesgFile;
            mesgFile = new std::ifstream("../config/msg.txt");

            mesgFile->getline(message_to_encrypt_char, MAX_LENGTH);
            unsigned int len = strlen(message_to_encrypt_char);

            //Encrypt, then decrypt the message
            std::cout << "Original text: " << message_to_encrypt_char << std::endl;
            convertChar2Long(message_to_encrypt_char, message_to_encrypt_long,false);


            //Encrypt
            std::ifstream pubkey;
            pubkey.open("../output/my_pub_key.txt");
            long long int key;
            long long int group;
            pubkey >> key >> group;

            if(key == 0){
                std::cout << std::endl << std::endl
                          << "Public key file, 'my_pub_key.txt', does not exist."
                          << std::endl << std::endl;
                continue;
            }

            encrypt(message_to_encrypt_long, key, group, message_to_decrypt_long, len*4);
            convertLong2Char(message_to_decrypt_long, message_to_decrypt_char,false);
            std::cout << "Encrypted text: " << message_to_decrypt_char << std::endl;
            std::ofstream enc_msg_txt;


            enc_msg_txt.open("../output/enc_msg.dat",std::ios::binary);
            for(int i = 0; i < int(sizeof(message_to_decrypt_long)/sizeof(message_to_decrypt_long[0])); i++){
                enc_msg_txt << message_to_decrypt_long[i] << "\n";
            }
            pubkey.close();
            enc_msg_txt.close();

        }

        else if (input == "dec"){

            std::ifstream encMesgFile;

            encMesgFile.open("../output/enc_msg.dat", std::ios::binary);
            for(int i = 0; i < int(sizeof(message_to_decrypt_long)/sizeof(message_to_decrypt_long[0])); i++){
                encMesgFile >> message_to_decrypt_long[i];
            }

            encMesgFile.close();
            //Decrypt

            std::ifstream privkey;
            privkey.open("../output/my_priv_key.txt");
            long long int key;
            long long int group;
            privkey >> key >> group;

            if(key == 0) {
                std::cout << std::endl << std::endl
                          << "Private key file, 'my_priv_key.txt', does not exist."
                          << std::endl << std::endl;
                continue;
            }

            decrypt(message_to_decrypt_long, key, group, decrypted_message_long, MAX_LENGTH*4);

            convertLong2Char(decrypted_message_long, decrypted_message_char,false);
            std::cout << "Decrypted text: " << decrypted_message_char << std::endl;
            std::ofstream dec_msg_txt;
            dec_msg_txt.open("../output/dec_msg.txt");
            dec_msg_txt << decrypted_message_char;
            dec_msg_txt.close();
        }
        else if (input == "eve"){

            std::ifstream pubkey;
            pubkey.open("../output/other_pub_key.txt");
            long long int intercepted_pub_key;
            long long int group;
            pubkey >> intercepted_pub_key >> group;
            if((intercepted_pub_key == 0) && (group == 0)){
                std::cout << std::endl << std::endl
                          << "Intercepted public key file, 'other_pub_key.txt', does not exist."
                          << std::endl << std::endl;
                continue;
            }
            PrimeClass pq = brute_force_exec(group);
            privateKeyGen(pq.p, pq.q, &group, &private_key, intercepted_pub_key);
            std::cout << "Brute Forced Private key: " << private_key << std::endl;
            std::ofstream brute_forced_key_file;
            brute_forced_key_file.open("../output/brute_forced_priv_key.txt");
            brute_forced_key_file << private_key << " " << group << "\n";
            brute_forced_key_file.close();
            pubkey.close();

        }
        else if (input == "unit") {

            unitTests();
        }
        else if (input == "exit") {

            return 0;
        }
        else {
            std::cout << "Invalid Input. Try again." << std::endl;
        }
    }
}

