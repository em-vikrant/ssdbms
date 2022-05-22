/* file		main.cpp
 * brief	This file contains the entry point (main-thread).
 */

/* Library includes. */
#include <iostream>
#include "student.h"
#include "DBManager.h"
#include "logger.h"

void misc_code();

int main() {
	Student ram("Ram", 1, 'A', "IIT");
	Student shyam("Shyam", 2, 'B', "NIT");
	Student govind("Govind", 1, 'C', "DTU");

	DB::DataBase db("StdTable");
	db.init();	// Initializing the database.

	ram.setUniqueId(db.insertEntry(ram));
	shyam.setUniqueId(db.insertEntry(shyam));
	govind.setUniqueId(db.insertEntry(govind));
	
	// ram.showData();
	// shyam.showData();
	// govind.showData();

	db.readEntry(ram.getUniqueId());
	db.readEntry(shyam.getUniqueId());
	db.readEntry(govind.getUniqueId());
	
	/* General section for code verification / testing. */
	misc_code();

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
