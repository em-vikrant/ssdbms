/* file		student.cpp
 * brief	This file implements student class.
 */

/* Library includes. */
#include <iostream>
#include "student.h"
#include "logger.h"


Student::Student(std::string sname, int srollNo, char sgrade, std::string suniv) {
	name = sname, 
	rollNo = srollNo;
	grade = sgrade;
	university = suniv;
	studentId = 0xffffffff;
}

void Student::setName(std::string sname) {
	name = sname;
}

void Student::setRollNo(int srollNo) {
	rollNo = srollNo;
}

void Student::setGrade(char sgrade) {
	grade = sgrade;
}

void Student::setUniversity(std::string suniv) {
	university = suniv;
}

void Student::setUniqueId(int uniqueId) {
	studentId = uniqueId;
}

std::string Student::getName() const {
	return name;
}

int Student::getRollNo() const {
	return rollNo;
}

char Student::getGrade() const {
	return grade;
}

std::string Student::getUniversity() const {
	return university;
}

int Student::getUniqueId() const {
	return studentId;
}

void Student::showData() const {
	LOG("Student Details.....\r\n");
	if(studentId == 0xffffffff) {
		LOG("ID\t\t: STUDENT NOT PRESENT IN DB\r\n");
	}
	else {	
		LOG("ID\t\t: %d\r\n", studentId);
	}
	LOG("NAME\t\t: %s\r\n", name);
	LOG("ROLLNO\t\t: %d\r\n", rollNo);
	LOG("GRADE\t\t: %c\r\n", grade);
	LOG("UNIVERSITY\t: %s\r\n", university);
}

