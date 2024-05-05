/* file		: student.h
 */

#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <vector>


class Student {
	public:

		Student(std::string name, char grade, std::string university);

        ~Student() {
            if (studentCount > 0)
                studentCount--;
        }

        /* Utility. */
        std::vector<char> getRaw();
        void createFromRaw(const std::vector<char>& rawData);
		
		/* Setters. */
		void setName(const std::string& sname);
		void setRollNo(const int& srollNo);
		void setGrade(const char& sgrade);
		void setUniversity(const std::string& uni);
		void setUniqueId(const std::string& uniqueId);
		
		/* Gettters. */
		std::string getName() const;
		int getRollNo() const;
		char getGrade() const;
		std::string getUniversity() const;
        std::string getUniqueId() const;
        int getApplicationNumber() const { return applicationNumber; }
		
		/* Display student's data. */
		void showData() const;

	private:
        
        static int studentCount;
        int applicationNumber;
		int rollNo;
		char grade;
		std::string name;
		std::string university;
        std::string uniqueId;
};

#endif
