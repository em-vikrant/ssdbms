/* file		Student.cpp
 * brief	This file implements Student class.
 */

/* Library includes. */
#include <iostream>
#include <algorithm>
#include "Student.h"
#include "logger.h"

/* Static variables. */
int Student::studentCount = 0;

Student::Student(std::string name, char grade, std::string university) {
	this->name = name, 
	this->grade = grade;
	this->university = university;
    this->rollNo = ++studentCount;
    applicationNumber = this->rollNo;
}

void Student::setName(const std::string& sname) {
	name = sname;
}

void Student::setRollNo(const int& srollNo) {
	rollNo = srollNo;
}

void Student::setGrade(const char& sgrade) {
	grade = sgrade;
}

void Student::setUniversity(const std::string& suniv) {
	university = suniv;
}

void Student::setUniqueId(const std::string& uniqueId) {
    this->uniqueId = uniqueId;
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

std::string Student::getUniqueId() const {
	return uniqueId;
}

void Student::showData() const {
	LOG("Student Details.....\r\n");
    LOG("ID\t\t: %s\r\n", uniqueId);
	LOG("ROLLNO\t\t: %d\r\n", rollNo);
	LOG("NAME\t\t: %s\r\n", name);
	LOG("GRADE\t\t: %c\r\n", grade);
	LOG("UNIVERSITY\t: %s\r\n", university);
}

std::vector<char> Student::getRaw() {
    int length = 0;

    length += sizeof(rollNo);
    length += sizeof(grade);
    length += name.length() + 1;
    length += university.length() + 1;
    length += uniqueId.length() + 1;

    std::vector<char> dataVec(length);
    char* pData = nullptr;
    int offset = 0;
    int memberLen = 0;

    pData = uniqueId.data();
    memberLen = uniqueId.length() + 1;
    std::copy(pData, pData + memberLen, dataVec.begin() + offset);
    offset += memberLen;

    pData = reinterpret_cast<char*>(&rollNo);
    memberLen = sizeof(rollNo);
    std::copy(pData, pData + memberLen, dataVec.begin() + offset);
    offset += memberLen;

    pData = name.data();
    memberLen = name.length() + 1;
    std::copy(pData, pData + memberLen, dataVec.begin() + offset);
    offset += memberLen;

    pData = reinterpret_cast<char*>(&grade);
    memberLen = sizeof(grade);
    std::copy(pData, pData + memberLen, dataVec.begin() + offset);
    offset += memberLen;

    pData = university.data();
    memberLen = university.length() + 1;
    std::copy(pData, pData + memberLen, dataVec.begin() + offset);
    offset += memberLen;

    return dataVec;
}

void Student::createFromRaw(const std::vector<char>& rawData) {

}


