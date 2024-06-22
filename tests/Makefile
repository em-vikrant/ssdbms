# file		Makefile
# brief		This file is used to automate the compilation for the test applications for student database management system.

CC=gcc
CXX=g++

PROJECT = tests
SRC_PATH=../$(TEST_PATH)
BIN_PATH=../$(BUILD_PATH)/$(PROJECT)
MAIN_INC_PATH=../$(INC_PATH)
MAIN_LIB_PATH=../$(LIB_PATH)
TEST_DIRS := DBManager_test

LIBS := -lDBManager -lStudent -lStudentManager

# Compilation Flags.
FLAGS = -std=c++17

.PHONY: all setup compile

all:
	@echo "BUILDING TESTS"
	@$(MAKE) setup
	@$(MAKE) compile
	@echo "BUILDING TESTS ...COMPLETE"

setup:
	@echo "SETTING UP TEST BUILDS"
	@for dir in $(TEST_DIRS); do \
		mkdir -p $(BIN_PATH)/$$dir; \
	done

compile:
	@echo "COMPILING TESTS"
	@for dir in $(TEST_DIRS); do \
		echo "COMPILE: $$dir"; \
		$(CXX) $(FLAGS)  $(SRC_PATH)/$$dir/*.cpp -I$(MAIN_INC_PATH) -o $(BIN_PATH)/$$dir/$$dir -L$(MAIN_LIB_PATH) $(LIBS) || \
		{ echo "COMPILE: $$dir ...FAILED"; exit 1; }; \
		echo "COMPILE: $$dir ...COMPLETE"; \
	done
	@echo "COMPILING TESTS ...COMPLETE"

