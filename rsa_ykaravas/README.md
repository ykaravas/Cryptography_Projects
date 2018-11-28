**README**

Included in this project is the full source code, written in C++ with the ability to 
encrypt, decrypt and eavesedropp/crack our relatively light version of the RSA algorithm.
I have added a few unit tests and as of this writing, hope to adde more, however, creating 
unittests in c++ is a bit more cumbersome and time consuming than most other languages. 
This document, is of course the Readme containing project requirements list, project
structure, build instructions, usage instructions on how to run the program and finally
a thorough description of the programs workflow, abilities and functions.


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

Once executable is run you will have several options:

	'gen' to generate key pairs (gen.txt file necessary)
	'enc' to encrypt message located in msg.txt (my_pub_key.txt file necessary)
	'dec' to decrypt message located in enc_msg.dat (my_priv_key.txt file necessary)
	'eve' to intercept message with public key and find p & q (other_pub_key.txt file necessary)
	'unit' to run unit tests
	'exit' to end program


Program will run on loop un til exit command is executed.


**Description**




