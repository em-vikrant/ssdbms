/* file		DBManager.cpp
 * brief	This file is responsible for DataBase operations. */

/* Library includes. */
#include <cstdio>
#include <fstream>
#include <cstring>
#include "logger.h"
#include "DBManager.h"

/* Implementation section. */
#define DB_PATH		"./db/"

const int maxRecLimit = MAX_RECORDS_COUNT;
const int maxRecSize = MAX_RECORDS_SIZE;
static FILE *fp = NULL;

enum fileMode {
	READ, WRITE, READ_WRITE, APPEND, READ_WRITE_PLUS
};

/* Useful utility functions. */
//-----------------------------------------------------------------------------------------

const char *fMode(int fileMode) {
	const char *mode = "r";
	switch(fileMode) {
		case READ:
			mode = "r";
			break;
		case WRITE:
			mode = "w";
			break;
		case READ_WRITE:
			mode = "r+";
			break;
		case APPEND:
			mode = "a";
			break;
		case READ_WRITE_PLUS:
			mode = "w+";
	}
	return mode;
}

std::string getStringObj(char *cstr) {
	std::string str((const char *)cstr);
	return str;
}

//-----------------------------------------------------------------------------------------

DB::DataBase::DataBase(std::string dbFile) {
	dbFileName = std::string(DB_PATH) + dbFile;
	entryCount = 0;
}

int DB::DataBase::init() {
	int ret = DB::SUCCESS;
	fp = fopen((const char *)dbFileName.c_str(), fMode(READ_WRITE_PLUS));
	if(!fp) {
		LOG("FAILED TO INITIALIZE DB\r\n");
		ret = DB::OPERATION_FAIL;
	}
	else {
		if(0 > fwrite((const void *)&entryCount, 1, sizeof(entryCount), fp)) {
			ret = DB::OPERATION_FAIL;
		}
		fclose(fp);
	}
	return ret;
}

int DB::DataBase::insertEntry(const Student& student) {
	char block[maxRecSize];
	int ret = DB::SUCCESS;

	entryCount++;
	dataForm df;
	
	df.uniqueId = entryCount;
	df.entry1 = student.getGrade();
	df.entry2 = student.getRollNo();
	strncpy(df.entry3, student.getName().c_str(), sizeof(df.entry3));
	strncpy(df.entry4, student.getUniversity().c_str(), sizeof(df.entry4));

	memcpy(block, &df, sizeof(df));	// Copy student entry into block buffer.
	
	/* Insert entry into file. */
	fp = fopen(dbFileName.c_str(), fMode(WRITE));	// Open file into write mode.
	if(!fp) {
		LOG("FAILED TO OPEN DB FILE\r\n");
		ret = DB::OPERATION_FAIL;
	}
	else {
		long int blockSize = sizeof(dataForm);
		long int offset = sizeof(entryCount) + entryCount * blockSize;
		fseek(fp, offset, SEEK_SET);
		if(0 > fwrite(block, 1, blockSize, fp)) {
			LOG("FAILED TO INSERT ENTRY INTO DB\r\n");
			entryCount--;
			ret = DB::OPERATION_FAIL;
		}
		else {
			ret = entryCount;	// To return unique-id for the entry.
		}
		fclose(fp);
	}
	return ret;
}

int DB::DataBase::deleteEntry(int uniqueId) {
	return 0;
}

int DB::DataBase::readEntry(int uniqueId) {
	dataForm df;
	int blockSize = sizeof(dataForm);
	int rBytes = 0;
	int offset = 0;
	bool entryFound = false;
	int ret = DB::SUCCESS;
	
	fp = fopen(dbFileName.c_str(), fMode(READ));
	if(!fp) {
		LOG("FAIL TO READ FROM DB FILE\r\n");
		ret = OPERATION_FAIL;
	}
	else {
		offset = sizeof(entryCount);
		fseek(fp, offset, SEEK_SET);	// Jumping through meta deta.

		while(fp) {
			memset(&df, 0, blockSize);
			rBytes = fread((void *)&df, 1, blockSize, fp);
			if(0 > rBytes) {
				break;
			}
			else if(df.uniqueId == uniqueId) {
				entryFound = true;
				break;	// Entry found so stop interating into file.
			}
		}
		
		/* Display entry when found. */
		if(entryFound) {
			st = new Student(getStringObj(df.entry3), df.entry2, df.entry1, getStringObj(df.entry4));
			st->setUniqueId(df.uniqueId);
			st->showData();
			delete st;	// Free the memory when entry displayed.
		}
		else {
			ret = OPERATION_FAIL;
		}
		fclose(fp);
	}
	return ret;
}

