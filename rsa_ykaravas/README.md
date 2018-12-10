**README**

Included in this project is the full source code, written in C++ with the ability to 
encrypt, decrypt and eavesdrop/crack our relatively light version of the RSA algorithm. 
Located in the repo is also a file with unit tests (4 of them running several iterations 
each) which provide fairly good coverage. This document, is of course the Readme 
containing project requirements list, project structure, build instructions, usage 
instructions on how to run the program and finally a thorough description of the 
programs workflow, abilities and functions.


**Requirements**


-g++ version 4.8 or higher

-make

-Only tested in Ubuntu 16.04 (not Windows or MAC)


**Structure**

	-rsa_ykaravas
		-src (dir)
			-*.cpp files
		-include (dir)
			-*.h files
		-build (dir)
			-*.o files
		-bin (dir)
			-binary executable "RSA"
		-config (dir)
			-*.txt *.dat files including public private key pair files, message files, 
			"intercepted" public key files etc...
		-testFiles
			-*.txt files used for unit testing
		-Makefile (file)


**Build**


in project root directory, run:

	make


OR


To build with OpenMP parallelization:

	make OMP=1



To Clean, from root directory run:

	make clean



**Run**

To run executable, navigate to ./bin directory and run:

	./RSA

(MUST be in bin directory when running in terminal for relative paths to work)

Once executable is run you will see this menu below.

                     MAIN PROGRAM FUNCTIONALITY & COMMAND LINE OPTIONS                    
        ------------------------------------------------------------------------------  
              'gen'           to generate key pairs for BOB and ALICE 
              'enc'           to encrypt message located in 'config/msg.txt' 
              'dec'           to decrypt message located in 'output/Alice/enc_msg.dat'  
              'eve'           to intercept ALICE message and BOB public key and find p & q 
              'msg'           to change message content in 'config/msg.txt' file. 
              'unit'          to run all unit tests
              'exit'          to end/exit program     
                               AUXILIARY FUNCTIONS  
        ------------------------------------------------------------------------------
              'factor'        to factor a number into two primes (if possible) 
              'gcd'           to find gcd of two numbers
              'prime'         to find if a number is prime or not
              'modexp'        to perform fast exponentiation


There are many options which will be discussed below. They can be run one after another since
the program will run on loop until exit command is executed.


**Description**


The first command that should be run is "gen" which stands for generate. The user will then be 
prompted to either opt to use the prime numbers located in the config/gen.txt file by typing
'c', or to use random pairs of primes located in config/primes.txt. Program will then check to 
make sure the numbers are in fact prime. At this stage, both Alice and Bob will be independently 
be generating their public and private keys. These keys are generated using the publicKeyGen and
privateKeyGen functions which both take as input the two prime numbers, p and q, the modulo, which
is (p-1)(q-1) and the address of the public key (to write to it); Of course the privateKeyGen 
function also takes the address of the private key. The privateKeyGen function finds a private 
key such that (priv * pub) modulo = 1. Once both Alice and Bob have generated their keys, they 
are saved to their respective directories, 'output/Alice' and 'output/Bob'.

After the "gen" stage is run at least once, the "enc" command, which stands for encrypt, can 
then be run. This command simulates Alice encrypting the config/msg.txt and sending it to Bob. 
This command prompts the program to load the config/msg.txt and Bob's public key. The message, once 
loaded is then processed in order to convert it from characters/bytes to integers so that it may be
properly encrypted. Once converted to integers, the encrypt function is called with Bob's public key
(exponent and modulo) and the message as input. The encrypt function uses the fast exponentiation to
encrypt the message using Bob's public key: encrypted_segment = (msg_segment*exponent)%modulo. Once 
the whole message is encrypted, this section writes out the encrypted message to Alice's directory 
(where Bob retrieves it from thus simulating the sending of the message to Bob).  

After "enc" is called, "dec" can be called which of course stands for decrypt. This section begins with
Bob loading (aka receiving) Alice's encrypted message and runs it through the decrypt function. This 
function is similar to the encrypt one except Bob loads his own private key, unlike Alice who loaded 
Bob's public key. This is because Bob's private key is the only thing that can decrypt something encrypted 
with his public key of course. The decrypt function take Bob's private key, the modulo and the message 
and much like the encryption algorithm, decrypts the message segment by segment using fast exponentiation. 
The decrypted message is the converted back to ascii characters from integers and is now legible. Bob
then saves the decrypted message to his output directory (as proof that it was decrypted). Throughout 
these processes, the user is also notified if the actions were successful.

Finally, the "eve" command can be used (but note that this can even be used directly after the "enc" 
). This command simulates Eve eavesdropping on the communications between Alice and Bob. Eve gets a
hold of Bob's public key (which is easily accessible by anyone) and intercepts the encrypted message 
which Alice had "sent" Bob earlier. Given that our primes are only on the order of 30 bits, it is fairly
easy for Eve to brute force factor bobs modulo into its two prime factors. This is how it is done here. I
am using an unrolled loop, skipping evens, optimizing compilation and of course it is written in C++ so 
for numbers this small this brute force approach, although bland, is effective. Once Eve has Bob's P and Q,
She can then use Bob's public key, modulo and P and Q to calculate his private key fairly easily and in 
turn decrypt Alice's message which was intended for Bob. This part of the program loads the original plain
text message and Bobs actual private key to check if the attack was successful. Eve then saves out the 
decrypted message along with Bob's compromised private key to Eve's directory (as proof).

There is also a "msg" command to allow user to more easily change the original plain text message that 
Alice sends to Bob without much manual effort. The "unit" command runs all the unit tests build for this 
program. There are four in total which each run anywhere from 8 - 15 iterations. The "exit" command will 
of course terminate the process. 

There are also four other commands I have added in order to make the building blocks/functions of the 
overall project a bit more accessible. These include "factor" which is comprised of the function Eve uses
to factor Bob's modulo into its two primes, "prime", to check if a number is prime, "gcd" to find the 
greatest common denominator of two numbers entered by the user and finally "modexp" which takes three
arguments, base, exponent and modulo and performs modular exponentiation (base^exponent)%modulo.

