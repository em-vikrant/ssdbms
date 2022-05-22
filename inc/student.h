/* file		: student.h
 */

#ifndef STUDENT_H
#define STUDENT_H


class Student {
	public:
		Student(std::string, int, char, std::string);
		
		/* Setters. */
		void setName(std::string sname);
		void setRollNo(int srollNo);
		void setGrade(char sgrade);
		void setUniversity(std::string uni);
		void setUniqueId(int uniqueId);
		
		/* Gettters. */
		std::string getName() const;
		int getRollNo() const;
		char getGrade() const;
		std::string getUniversity() const;
		int getUniqueId() const;
		
		/* Display student's data. */
		void showData() const;

	private:
		mutable int studentId;
		std::string name;
		int rollNo;
		char grade;
		std::string university;
};

#endif
