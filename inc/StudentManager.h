/* file     IdGenerator.h
 * brief    header file for StudentManager class.
 */

#ifndef _ENABLE_STUDENTMANAGER_H_
#define _ENABLE_STUDENTMANAGER_H_

#include <map>

#include "Student.h"


class StudentManager {
    public:
        static StudentManager& getInstance() {
            static StudentManager instance;
            return instance;
        }

        std::shared_ptr<Student> createStudent(std::string, char, std::string);
        std::shared_ptr<Student> parseStudentData(const std::vector<char>& studentData);

        void printStudentRecords();

    private:
        static StudentManager m_Instance;
        std::map<std::string, std::shared_ptr<Student>> studentMap;

        // Singleton class: Non-instanciation, non-copyable
        StudentManager() {}

        StudentManager(const StudentManager&) = delete;
        StudentManager& operator=(const StudentManager&) = delete;

        // Private utitlity methods
        std::string createUniqueId(std::shared_ptr<Student>& pStudent);
};

#endif
