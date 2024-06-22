# file		Makefile
# brief		This file is used to automate the compilation for the student database management system.

PROJECT := "STUDENT DATABASE MANAGEMENT SYSTEM"

CC=gcc
CXX=g++

APP=sdbms
APP_PATH=./
INC_PATH=./inc
SRC_PATH=./src
LIB_PATH=./lib
BUILD_PATH=./build
TEST_PATH=./tests

export INC_PATH
export LIB_PATH
export BUILD_PATH
export TEST_PATH

# SFML include path
export SFML_INC_PATH=$(APP_PATH)../SFML/include
export SFML_LIB_PATH=$(APP_PATH)../SFML/build/lib

# libraries used.
SFML_LIBS = -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -lsfml-network
STD_LIBS = -lpthread

# Configuration options
OPT_ENABLE_TEST := ON
OPT_ENABLE_DEBUG := OFF #TODO: Need to handle ON condition

# Compilation Flags.
FLAGS = -std=c++17

# ----------------------
# Targets to execute
# ----------------------

FILES := Student StudentManager DBManager Display

.PHONY: clean_lib $(FILES) all tests

all:
	@echo "PROJECT: $(PROJECT)\n"
	@echo "BUILDING $(PROJECT)"
	@echo "----------------------------"
	@echo "PROJECT COMPILATION"
	@echo "OPT_ENABLE_DEBUG = $(OPT_ENABLE_DEBUG)"
	@$(MAKE) source
	@install_name_tool -add_rpath @executable_path/../../SFML/build/lib $(BUILD_PATH)/$(APP)
	@echo "PROJECT COMPILATION ...COMPLETE"
	@echo "============================"
	@echo "EXECUTABLE PATH : $(BUILD_PATH)/$(APP)"
	@echo "============================"
	@echo "BUILDING $(PROJECT) ...COMPLETE\n"

source: $(FILES) tests
	@$(CXX) $(FLAGS) -MMD -MP $(LIB_PATH)/* main.cpp -I$(INC_PATH) -I$(SFML_INC_PATH) -o $(BUILD_PATH)/$(APP) -L$(SFML_LIB_PATH) $(SFML_LIBS)

$(FILES):
	@echo "COMPILE: $@"
	@$(CXX) $(FLAGS) -c $(SRC_PATH)/$@.cpp -I$(INC_PATH) -I$(SFML_INC_PATH) -o $(LIB_PATH)/$@.o -L$(SFML_LIB_PATH) $(LDLIBS)
	@ar rcs $(LIB_PATH)/lib$@.a $(LIB_PATH)/$@.o
	@rm $(LIB_PATH)/$@.o
	@echo "COMPILE: $@ ...COMPLETE"

tests:
ifeq ($(OPT_ENABLE_TEST),ON)
	@echo "OPT_ENABLE_TEST = $(OPT_ENABLE_TEST)"
	@make -C $(TEST_PATH)
endif

clean_lib:
	@echo "CLEANING LIB DIRECTORY"
	@rm -f $(LIB_PATH)/*

clean: clean_lib
	@echo "CLEANING BUILD DIRECTORY"
	@rm -fr $(BUILD_PATH)

fresh:
	@echo "MAKE FRESH BUILD"
	@$(MAKE) clean
	@echo "----------------------------\n"
	@$(MAKE) all


