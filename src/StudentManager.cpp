/* file		StudentManager.cpp
 * brief	This file implements StudentManager class.
 */

/* Library includes. */
#include <iostream>
#include <algorithm>
#include "logger.h"
#include "StudentManager.h"


std::string StudentManager::createUniqueId(std::shared_ptr<Student>& pStudent) {
    std::string uniqueId = "";

    uniqueId += std::to_string(pStudent->getRollNo()) + "_";
    uniqueId += pStudent->getName() + "_";
    uniqueId += std::string(1, pStudent->getGrade()) + "_";
    uniqueId += pStudent->getUniversity();
    
    return uniqueId;
}

std::shared_ptr<Student>
StudentManager::createStudent(std::string name, char grade, std::string university) {
    std::shared_ptr<Student> pStudent = nullptr;

    // Check if student is already in the map
    for (auto [key, value] : studentMap) {
        std::shared_ptr<Student> ps = value;
        if (ps->getName() == name && ps->getGrade() == grade && ps->getUniversity() == university) {
            pStudent = ps;
            break;
        }
    }

    if (pStudent != nullptr) {
        return pStudent;
    }
    
    pStudent = std::make_shared<Student>(name, grade, university);
    std::string uniqueId = createUniqueId(pStudent);

    // Set the unique id for this newly created student
    // Also add entry in the map
    pStudent->setUniqueId(uniqueId);
    studentMap[uniqueId] = pStudent;
    
    return pStudent;
}

std::shared_ptr<Student> StudentManager::parseStudentData(const std::vector<char>& studentData) {
    std::string uniqueId = "";
    std::shared_ptr<Student> pStudent = nullptr;
    int offset = 0;

    // lambda function to copy until a char is found.
    auto copyUntilChar = [&](std::string& str, 
            const std::vector<char>& data,
            int idx,
            char ch) -> int {
        int i = idx;
        for (; i < data.size(); i++) {
            if (data[i] == ch)    break;
            str += data[i];
        }
        return i;
    };

    offset = copyUntilChar(uniqueId, studentData, offset, '\0');
    offset++;

    // Check if already in the student map.
    if (studentMap.count(uniqueId) == 0) {
        // Create a student from the data
        // Get Roll No
        std::string name = "";
        std::string university = "";
        char grade;
        int rollNo;

        //Get RollNo
        rollNo = (studentData[offset] << 8 | studentData[offset + 1]);
        offset += 2;

        // Get Name
        offset = copyUntilChar(name, studentData, offset++, '\0');

        // Get grade
        grade = studentData[offset++];

        // Get University
        offset = copyUntilChar(university, studentData, offset++, '\0');

        // Create student
        pStudent = createStudent(name, grade, university);
        pStudent->setRollNo(rollNo);
    }
    else {
        pStudent = studentMap[uniqueId];
    }

    return pStudent;
}

std::vector<char> StudentManager::getRawDataForStudent(const std::string& studentId) {
    // TODO: Shifting this method from Student to here.
    return std::vector<char>(0);
}

void StudentManager::printStudentRecords() {
    LOG("STUDENT MANAGER, NUMBER OF RECORDS, %d\n", studentMap.size());
    for (auto pStudent : studentMap) {
        pStudent.second->showData();
        LOG("\n");
    }
}

std::vector<std::string> StudentManager::getStudentIdList() {
    std::vector<std::string> studentIdVec; 
    for (auto [key, value] : studentMap) {
        studentIdVec.push_back(key);
    }
    return studentIdVec;
}

std::vector<std::shared_ptr<Student>> StudentManager::getStudentList() {
    std::vector<std::shared_ptr<Student>> studentVec; 
    for (auto [key, value] : studentMap) {
        studentVec.push_back(value);
    }
    return studentVec;
}


