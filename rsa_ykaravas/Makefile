ifeq ($(OMP),1)
	CFLAGS += -fopenmp
endif

SRC_DIR = ./src
INC_DIR = ./include
OBJ_DIR = ./build
BIN_DIR = ./bin
CONFIG_DIR = ./config
OUTPUT_DIR = ./output

CC = g++-4.8
CXX = g++
CXXFLAGS =  -m64 -std=c++11 -Wall -g -I$(INC_DIR)
EXPENDABLES = PrimeClass.o RSA.o CoreFunctions.o unittests.o RSA


all:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
	@make $(EXPENDABLES) 

RSA: RSA.o PrimeClass.o
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(OBJ_DIR)/PrimeClass.o $(OBJ_DIR)/unittests.o $(OBJ_DIR)/CoreFunctions.o $(OBJ_DIR)/RSA.o -lm -o $(BIN_DIR)/RSA

RSA.o: $(SRC_DIR)/RSA.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) -o $(OBJ_DIR)/$@ -c $<

PrimeClass.o: $(INC_DIR)/PrimeClass.h $(SRC_DIR)/PrimeClass.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/PrimeClass.cpp -o $(OBJ_DIR)/PrimeClass.o

CoreFunctions.o: $(INC_DIR)/CoreFunctions.h $(SRC_DIR)/CoreFunctions.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/CoreFunctions.cpp -o $(OBJ_DIR)/CoreFunctions.o

unittests.o: $(INC_DIR)/unittests.h $(SRC_DIR)/unittests.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/unittests.cpp -o $(OBJ_DIR)/unittests.o


clean:
	rm -f $(BIN_DIR)/RSA $(OUTPUT_DIR)/Alice/enc_msg.dat $(OUTPUT_DIR)/Bob/dec_msg.txt 
	rm -f $(OUTPUT_DIR)/Alice/priv_key.txt $(OUTPUT_DIR)/Alice/pub_key.txt 
	rm -f $(OUTPUT_DIR)/Bob/pub_key.txt $(OUTPUT_DIR)/Eve/brute_forced_priv_key.txt
	rm -f $(OBJ_DIR)/PrimeClass.o $(OBJ_DIR)/RSA.o $(OBJ_DIR)/CoreFunctions.o
	rm -f $(OBJ_DIR)/unittests.o $(OUTPUT_DIR)/Bob/priv_key.txt $(OUTPUT_DIR)/Eve/intercepted_msg.txt
