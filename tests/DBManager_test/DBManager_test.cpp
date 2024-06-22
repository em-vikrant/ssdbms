/* file		DBManager_test.cpp
 * brief	This file tests the functionality of DBManager with student data.
 */

/* Library includes. */
#include <iostream>
#include <set>
#include <cstring>
#include "DBManager.h"
#include "Student.h"
#include "StudentManager.h"
#include "logger.h"

void create_test_data(StudentManager& sm) {
    sm.createStudent("Ram", 'A', "IIT");
	sm.createStudent("Shyam", 'B', "NIT");
	sm.createStudent("Govind", 'C', "DTU");

    LOG("______________STUDENT MANAGER RECORDS CREATED_________________\r\n");
    sm.printStudentRecords();
}

void insert_test_data(StudentManager& sm, DB::DataBase& db) {
    db.init();

    LOG("---------------STUDENT DATA INSERTION----------------\r\n");
    for (auto student : sm.getStudentList()) {
        student->showData();
        DB::opStatus_t ret;
        if (DB::SUCCESS != (ret = db.insertEntry(student))) {
            LOG("Failed to insert student data into the database!, %d\n", ret);
        }
        else {
            LOG("Insertion success\r\n");
            LOG("\n");
        }
    }
}

void read_test_data(std::vector<std::string> studentIdList, DB::DataBase& db) {
    LOG("---------------STUDENT DATA RETRIEVAL----------------\r\n");
    for (std::string& id : studentIdList) {
        for (char ch : db.readEntry(id)) {
            LOG("%c", ch);
        }
        LOG("\n");
    }
}


int main() {
    LOG("## TEST: DBManager\n");

    StudentManager& studentManager = StudentManager::getInstance();
	DB::DataBase db("DBManager_test.dat");

    create_test_data(studentManager);
    insert_test_data(studentManager, db);
    read_test_data(studentManager.getStudentIdList(), db);
}


