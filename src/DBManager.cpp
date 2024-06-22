/* file		DBManager.cpp
 * brief	This file is responsible for DataBase operations. */

/* Library includes. */
#include <cstdio>
#include <fstream>
#include <cstring>
#include <sstream>
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
			mode = "a+";
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
	fp = fopen(dbFileName.c_str(), fMode(READ_WRITE_PLUS));
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

DB::opStatus_t DB::DataBase::insertEntry(const std::shared_ptr<Student> student) {
	char block[maxRecSize];
    DB::opStatus_t ret = DB::SUCCESS;

	entryCount++;

    std::vector<char> dataFrame;
    std::vector<char> dataVec = student->getRaw(); // Get the raw data stream for the student

    /* Create data frame. */
    dataFrame.insert(dataFrame.end(), FRAME_HEADER.begin(), FRAME_HEADER.end());
    dataFrame.insert(dataFrame.end(), dataVec.begin(), dataVec.end());
    dataFrame.insert(dataFrame.end(), FRAME_FOOTER.begin(), FRAME_FOOTER.end());
    
	/* Insert entry into file. */
	fp = fopen(dbFileName.c_str(), fMode(APPEND));	// Open file into append mode.
	if(!fp) {
		LOG("FAILED TO OPEN DB FILE\r\n");
		ret = DB::OPERATION_FAIL;
	}
    else {
        /* Insert the entry in DB at end. */
        fseek(fp, 0, SEEK_END);
        if(0 > fwrite(dataFrame.data(), 1, dataFrame.size(), fp)) {
            LOG("FAILED TO INSERT ENTRY INTO DB\r\n");
            entryCount--;
            ret = DB::OPERATION_FAIL;
        }
        else {
            //LOG("INSERT ENTRY, DF --[ ");
            //for (char c : dataFrame)
            //    LOG("%c ", c);
            //LOG("]\r\n");
            /* Update the entry count on successful insertion. */
            fseek(fp, 0, SEEK_SET);
            if(0 > fwrite((const void *)&entryCount, 1, sizeof(entryCount), fp)) {
                LOG("FAILED TO UPDATE THE ENTRY COUNT IN DB\r\n");
                ret = DB::OPERATION_FAIL;
            }
        }
        fclose(fp);
    }
	return ret;
}

int DB::DataBase::deleteEntry(int uniqueId) {
	return 0;
}

std::vector<char> DB::DataBase::readEntry(const std::string& id) {
    std::vector<char> buffer(150);
    std::vector<char> data;
    int rBytes = 0;
    int offset = 0;
    bool entryFound = false;
    int ret = DB::SUCCESS;

    auto printBuffer = [&](std::vector<char>& buf) {
        LOG(" %d, [ ", buf.size());
        for (char ch : buf) {
            LOG("%c:%02x ", ch, ch);
        }
        LOG("]\n");
    };

    fp = fopen(dbFileName.c_str(), fMode(READ));
    if(!fp) {
        std::ostringstream oss;
        oss << "FAIL TO READ FROM DB FILE";
        throw std::runtime_error(oss.str());
    }
    else {
        offset = sizeof(entryCount);
        memset(buffer.data(), 0, buffer.size());

        while(fp) {
            fseek(fp, offset, SEEK_SET);
            rBytes = fread((void *)buffer.data(), 1, buffer.size(), fp);
            if(0 >= rBytes) {
                break;
            }
            else {
                const std::string_view& fh = FRAME_HEADER;
                const std::string_view& ff = FRAME_FOOTER;

                while (buffer.size() > (FRAME_HEADER.size() + FRAME_FOOTER.size())) {
                    auto headerPos = std::search(buffer.begin(), buffer.end(), fh.begin(), fh.end());
                    auto footerPos = std::search(buffer.begin(), buffer.end(), ff.begin(), ff.end());

                    // If frame header & footer are found
                    if ((headerPos != buffer.end() && footerPos != buffer.end()) && headerPos < footerPos) {
                        std::copy(headerPos + fh.size(), footerPos, std::back_inserter(data));

                        if (id == StudentManager::getInstance().parseStudentData(data)->getUniqueId()) {
                            entryFound = true;
                            break;
                        }

                        /* Clear the complete frame. */
                        buffer.erase(buffer.begin(), footerPos + ff.size());

                        /* Clear the data buffer. */
                        data.clear();
                    }
                    else { // if no frame found then break and read further data.
                        break;
                    }
                }
            }

            if (entryFound)
                break;

            /* To read next bytes. */
            offset += rBytes;
        }

        if(!entryFound) {
            ret = OPERATION_FAIL;
        }
        fclose(fp);
    }
    return data;
}

