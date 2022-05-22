/* file		DBManager.h
*/

#include "student.h"

#define MAX_RECORDS_SIZE	200
#define MAX_RECORDS_COUNT	100

namespace DB {

	enum dbOperatonReturns {
		SUCCESS			= 0,
		OPERATION_FAIL	= -1,
		INVALID_SIZE	= -2,
		INVALID_DATA	= -3,
		TIMEOUT_ERR		= -200
	};

	struct dataForm {
		int uniqueId;

		char entry1;
		int entry2;
		char entry3[50];
		char entry4[100];	
	};

	class DataBase {
		public:
			DataBase(std::string);
			int init();
			int insertEntry(const Student& student);
			int deleteEntry(int entryNumber);
			int readEntry(int uniqueId);

		private:
			std::string dbFileName;
			Student *st = nullptr;
			int entryCount;
	};
	
	int mapStdDataWithEntry(const dataForm& df, Student& student);
};
