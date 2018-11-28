**README**


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

	Possible Commands:

			  gen - This will prompt user for a large prime number. Can also
					type 'rand' instead of a large prime which will choose
					prime from primes.txt file in Generated_Files directory.
			  enc - Alice will encrypt original_msg.txt in her directory
			  dec - Bob will decrypt the message previously encrypted by Alice
			  eve - Eve will simulate MITM attack by taking Alice's Public key
					and encrypted message and cracking them.
			  msg - Change message in 'Generated_Files/Alice/original_msg.txt' file.
			purge - Remove all files except Generated_Files/Alice/original_msg.txt
					and Generated_Files/primes.txt
			 exit - Will exit program


	Enter Desired Command: 


All the necessary commands are explained above. Note that "enc" must be run at least once
before "dec" or "eve" and "gen" must be run once before all of them to initiate key 
creation/exchnage. Purge will delete all files in actor directories except for Alice's
original_msg.txt. Promgram can handle any input to be encrypted.Program will run on loop 
until exit command is executed.


**Description**





