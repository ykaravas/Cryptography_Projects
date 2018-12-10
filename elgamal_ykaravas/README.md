**README**

Included in this project is the full source code, written in Python with the ability 
for Alice to Encrypt and "send" to Bob, Bob to receive and decrypt from Alice and Eve 
to "listen in" and crack their private keys and encrypted messages. Unittest source 
code is also included in the root level directory of this project. This readme also
includes requirements for the program (of which there are very few), a description
of the project directory structure and files, directions on how to run it and a 
detailed description of the program's inner workings from the point of view of Alice,
Bob and Eve. 


**Requirements**


-python 3.4 or higher

-Tested on Ubuntu and Windows machines

Necessary python imports (all should be standard except
possibly unittest)

	import random
	import math
	import sys
	import os
	import unittest


**Structure**

	-elgamal_ykaravas
		-elgamal.py (main src file)
		-unit_test.py (unit testing file) 
		-Generated_Files (dir)
			-primes.txt (file with a bunch of large primes)
			-Alice (dir)
				-original_msg.txt (plain text message to be encrypted)
				-my_private_key.txt (Alice's private key)
				-my_public_key.txt (Alice's public key)
				-encrypted_msg.txt (encrypted message by Alice)
			-Bob (dir)
			  	-decrypted_msg.txt (decrypted message by Bob from Alice)
				-my_private_key.txt (Bob's private key)
				-my_public_key.txt (Bob's public key)
			-Eve (dir)
				-cracked_private_key.txt (Eve's version of Bob's key)
				-decrypted_intercepted_msg.txt (Eve's version of Alice's Encrypted message)
      


**Run**

Make sure your version of python is greater than 3.4.

To run executable, from root directory run:

    python elgamal.py


To run unittests, from root directory run:

    python -m unittest discover -s ./ -p *_test.py


NOTE* that your python alias "python" may be linked to python2.7 so you may need
to run above commands with python<version_num> file.py instead. e.g. python3.5 elgamal.py


When program is started, you shoud see the following:


	               MAIN PROGRAM FUNCTIONALITY & COMMAND LINE OPTIONS:
	---------------------------------------------------------------------------------
			  gen  		This will generate keys for Alice and Bob using BBS. Alice
			      		is the one who "posts" her choices for Bob to use.
			  enc  		Alice will encrypt original_msg.txt in her directory
			  dec   	Bob will decrypt the message previously encrypted by Alice
			  eve   	Eve will simulate MITM attack by taking Alice's Public key
			        	and encrypted message and cracking them.
			  msg   	to change message in 'Generated_Files/Alice/original_msg.txt' file.
			purge   	to remove all files except original_msg.txt and primes.txt
			 exit   	to terminate program
			 
	                             AUXILIARY FUNCTIONS
	---------------------------------------------------------------------------------
			  gcd   	to find gcd of two numbers
			prime   	to find if a number is prime or not
			modexp  	to perform fast exponentiation


Enter Desired Command: 


All the necessary commands are explained above. Note that "enc" must be run at least once
before "dec" or "eve" and "gen" must be run once before all of them to initiate key 
creation/exchange. Purge will delete all files in actor directories except for Alice's
original_msg.txt. The program can handle any input to be encrypted. Program will run on loop 
until exit command is executed.

**Functions**

I/O Helper Functions:

	- Read key or Message from File: readKeyOrMsg
	- Write key or message to file: writeKeyOrMsg
	- Displays options to user in terminal: displayOptions
	- Remove all files generated during execution: cleanFiles
	- Helper Function to allow strings as input: convertBytes2Ints
	- Helper Function to allow strings as input: convertInts2Bytes


Math/Crypto Helper Functions:

	- Calculate the number of bits in number: calcNumBits
	- Fast modular Exponentiation: fastModular
	- Get the secret key: getSecret
	- Get the multiplicative inverse of secret key: getMultInv
	- Find primitive Root: findPrimitiveRoot
	- Find GCD: extendedEuclidianGCD


Core Functions:

	- Generate Alice and Bob's keys: generateKeys
	- Factorization algorithm: bigStepLittleStep
	- Primality testing function: millerRabin
	- BlumBlumShub (BBS.py) function used internally to generate prime: getPrime
	- BlumBlumShub (BBS.py) function used internally to generate Large N: generateGroupN
	- BlumBlumShub (BBS.py) function to calculate number of bits: calcBits
	- BlumBlumShub (BBS.py) function used to obtain random prime: next
	- Core function used to encrypt: encrypt
	- Core function used to decrypt: decrypt
	- Main worker function which runs in loop: run
	- Main execution function: main

Obsolete Functions:
	- Find GCD: gcd


**Description**


The first command that should be run is "gen" which stands for generate. The User will be prompted
to enter the number of bits to use in key generation for size of N. The program will then check to 
make sure the bit number entered is evenand is at least 20 bits. This bit number is used to generate
a large N along with Alice and Bob's private numbers using BlumBlumShub. The program then simulates Alice 
using the large N to generate her public and private keys using a function called generateKeys. 
When Alice generates her keys, she does not pass the optional primitive root argument to the generate 
function but rather the function chooses one using a findPrimitiveRoot function along with a 
moduloExponent function. Bob will later use this same coprime to generate his keys. This function 
generates Alice's public key which consists of the original large N, which represents the group, 
a coprime, and the same raised to the power of her secret number mod the large N. Note that is 
this function of course also chooses her random integer from the group over the large N. The private 
key consists of the large N, coprime and secret key. Note* BlumBlumShub is used for generation of 
random primes in the key generation scheme. Miller Rabin is used to test primality.

This process is repeated for Bob with the minor difference, however, that Bob uses the group number
along with the coprime that Alice has "published" in order to generate his keys. Their keys are saved
in the Generated_Files/Alice and Generated_Files/Bob directories, respectively. Alice's directory
also starts out with the original_msg.txt file which can be edited manually or via the "msg" 
command of the program which will then prompt the user to enter the new plain text message that 
Alice will eventually encrypt and "send" to Bob. 

The "enc" command, which stands for encrypt, can then be run. This command simulates Alice encrypting
the original_msg.txt and sending it to Bob. This command prompts the program to load the origuinal_msg.txt,
Alice's private key and Bob's public key. Next, the encrypt function is called with the three variables, 
just mentioned, as arguments. The first thing this function does is compute the shared secret key using
Alice's private number in her private key in conjunction with Bob's coprime raised to his private number
modulo the group prime (this was the third component of Bob's public key). Next, the function converts
the string input from char bytes to ints so it can be encrypted. These integers are multiplied by the 
shared secret key and the product is modded by the group prime. Finally the encrypted output is saved to 
Alice's directory (where Bob retrieves it from thus simulating the sending of the message to Bob).  

After "enc" is called, "dec" can be called which of course stands for decrypt. This function is similar 
to the encrypt one except Bob loads his own private key, Alice's public key and the encrypted message. 
The decrypt function takes all these as arguments and uses the third part of Alice's public key,
coprime^her_private mod group_prime, along with Bob's private number in his private key to calculate 
the secret shared key. The decrypt function, of course, has to go one step further and calculate the 
multiplicative inverse of the secret shared key as well in order to decrypt. This is done by raising 
the secret shared key ^ (group prime - 2) mod group prime. The encrypted message, still in the form of
discreet integers, are multiplied by the multiplicative inverse of secret shared key and the product is
modded by the group prime. Finally, the message is then converted back to ascii characters. The decrypted
message is save to Bob's directory as proof that he has successfully decrypted it. The user in notified 
throughout each of these processes if they were successful or not. 

Finally, the "eve" command can be used (but note that this can even be used directly after the "enc" 
). This command simulates Eve eavesdropping on the communications between Alice and Bob. Eve gets a
hold of Bob's public key (which is easily accessible by anyone) and intercepts the encrypted message 
which Alice had "sent" Bob earlier. Given that our primes are only on the order of 30 bits, it is fairly
easy for Eve to brute force Bob's private number (the secret part of his private key) using the big 
step little step algorithm. Once she does this, she can access Alice's public key and use that along
with Bob's private key in order to derive the shared secret key and decrypt the encrypted message. The
program then proceeds to call decrypt using these parameters, decrypts the message, loads the original 
message from Alice's directory and compares the two for testing purposes in order to notify the user if 
Eve was successful or not. Eve then saves the cracked message and secret key in her directory as proof
of her success.

There is also a purge command to get rid of every .txt file in case one wants to start fresh. Although 
this is really no different from simply calling the "gen" function again since everyone's keys will be 
regenerated rather than deleted. Finally, the "exit" command exits from the program. The unit tests can 
be run separately using the command given above. 

This description was written prior to any collaboration with my team yet. As one can imagine, however,
the process my program will undergo during the collaboration process will be identical aside from 
manual replacement of keys and messages with those provided by my project mates. 

There are also three other commands I have added in order to make the building blocks/functions of the 
overall project a bit more accessible. These include "prime", to check if a number is prime, "gcd" to 
find the greatest common denominator of two numbers entered by the user and finally "modexp" which takes 
three arguments, base, exponent and modulo and performs modular exponentiation (base^exponent)%modulo.
























