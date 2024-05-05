/* file		main.cpp
 * brief	This file contains the entry point (main-thread).
 */

/* Library includes. */
#include <iostream>
#include <set>
#include <cstring>
#include "DBManager.h"
#include "Student.h"
#include "StudentManager.h"
#include "Display.h"
#include "logger.h"

void misc_code();

int main() {
#if 0
    StudentManager& studentManager = StudentManager::getInstance();
    std::set<std::shared_ptr<Student>> studentSet;

    studentSet.insert(studentManager.createStudent("Ram", 'A', "IIT"));
	studentSet.insert(studentManager.createStudent("Shyam", 'B', "NIT"));
	studentSet.insert(studentManager.createStudent("Govind", 'C', "DTU"));

	DB::DataBase db("student_data.dat");
	db.init();	// Initializing the database.

    LOG("---------------STUDENT DATA INSERTED----------------\r\n");
    for (auto student : studentSet) {
        student->showData();
        int ret = 0xffffffff;
        if (DB::SUCCESS != (ret = db.insertEntry(student->getRaw())))
        {
            LOG("Failed to insert student data into the database!, %d\n", ret);
        }
        LOG("\n");
    }

    // 1. Change the database code. Use fstream objects instead of c-style file i/o s.
    // 2. Show all entries of the database in a table on gui. Handle it on gui part.

    LOG("---------------STUDENT DATA RETRIEVED----------------\r\n");
    for (auto student : studentSet) {
        for (char ch : db.readEntry(student->getUniqueId())) {
            LOG("%c", ch);
        }
        LOG("\n");
    }

    LOG("______________STUDENT MANAGER RECORDS_________________\r\n");
    studentManager.printStudentRecords();
	
	/* General section for code verification / testing. */
	//misc_code();
    LOG("------2-------\r\n");
#elif 1
    sf::RenderWindow window;
    sf::Vector2f dimensions = {800, 600};
    std::string title = "SSDBMS: Student Database Manager";
    window.create(sf::VideoMode(dimensions.x, dimensions.y), title);

    // Elements
    sf::RectangleShape rec;

    sf::Event event;
    bool running = true;
    while (running) {
        // Polling events;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        window.clear(sf::Color::White);
        window.display();
    }
#endif

	return 0;
}

void misc_code() {
#ifndef MISC_CODE
	Print("_______________PRACTICE SECTION_______________\r\n");
	std::string str1 = "hello world!";
	std::string str2 = str1;
	std::string str3 = "New One";

	Print("String1[%s], String2[%s]\r\n", str1, str2);
	str2[3] = 'R';
	Print("String1[%s], String2[%s]\r\n", str1, str2);
	str2 = str3;
	str3 = "A very new dynamic";
	Print("String1[%s], String2[%s], String3[%s]\r\n",
			str1, str2, str3);
#endif
}
