# file		Makefile
# brief		This file is used to automate the compilation for the student database management system.

CC=gcc
CXX=g++

APP=sdbms
APP_PATH=./
INC_PATH=./inc
SRC_PATH=./src
LIB_PATH=./lib

# Standard libraries used.
STD_LIBS=-libm

# Compilation Flags.
FLAGS= -DMISC_CODE

clean:
	rm -f $(LIB_PATH)/*

student:
	$(CXX) $(FLAGS) -c $(SRC_PATH)/student.cpp -I $(INC_PATH) -o $(LIB_PATH)/student.o $(STD_LIBS)

database:
	$(CXX) $(FLAGS) -c $(SRC_PATH)/DBManager.cpp -I $(INC_PATH) -o $(LIB_PATH)/DBManager.o $(STD_LIBS)

all: clean student database
	$(CXX) $(FLAGS) $(LIB_PATH)/* main.cpp -I $(INC_PATH) -o $(APP)

