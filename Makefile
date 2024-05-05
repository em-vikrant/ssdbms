# file		Makefile
# brief		This file is used to automate the compilation for the student database management system.

CC=gcc
CXX=g++

APP=sdbms
APP_PATH=./
INC_PATH=./inc
SRC_PATH=./src
LIB_PATH=./lib

# SFML include path
SFML_INC_PATH=$(APP_PATH)../SFML/include
SFML_LIB_PATH=$(APP_PATH)../SFML/build/lib

# libraries used.
SFML_LIBS = -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -lsfml-network
STD_LIBS= -lpthread

# Compilation Flags.
FLAGS= -std=c++17 # -DMISC_CODE

# Setting the rpath for the executable 

clean:
	rm -f $(LIB_PATH)/*

student:
	$(CXX) $(FLAGS) -c $(SRC_PATH)/Student.cpp -I $(INC_PATH) -o $(LIB_PATH)/Student.o $(STD_LIBS)

student_manager:
	$(CXX) $(FLAGS) -c $(SRC_PATH)/StudentManager.cpp -I $(INC_PATH) -o $(LIB_PATH)/StudentManager.o $(STD_LIBS)

database:
	$(CXX) $(FLAGS) -c $(SRC_PATH)/DBManager.cpp -I $(INC_PATH) -o $(LIB_PATH)/DBManager.o $(STD_LIBS)

display:
	$(CXX) $(FLAGS) -c $(SRC_PATH)/Display.cpp -I$(INC_PATH) -I$(SFML_INC_PATH) -o $(LIB_PATH)/Display.o -L$(SFML_LIB_PATH) $(STD_LIBS) $(SFML_LIBS)

all: clean student student_manager database display
	$(CXX) $(FLAGS) $(LIB_PATH)/* main.cpp -I$(INC_PATH) -I$(SFML_INC_PATH) -o $(APP) -L$(SFML_LIB_PATH) $(SFML_LIBS)
	install_name_tool -add_rpath @executable_path/../SFML/build/lib $(APP)

debug: clean student student_manager database
	$(CXX) $(FLAGS) $(LIB_PATH)/* main.cpp -I $(INC_PATH) -o $(APP)
