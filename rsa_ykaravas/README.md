**README**


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
      -*.txt *.dat files including public private 
       key pair files, message files, "intercepted"
       public key files etc...
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



