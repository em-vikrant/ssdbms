/* file		DBManager.h
 * Header file for the Data Base Manager class.
 */

#include <vector>
#include <string_view>
#include "Student.h"
#include "StudentManager.h"


#define MAX_RECORDS_SIZE	200
#define MAX_RECORDS_COUNT	100


namespace DB {

    constexpr std::string_view FRAME_HEADER = "**FH**";
    constexpr std::string_view FRAME_FOOTER = "**FF**";

	enum opStatus_t {
		SUCCESS			= 0,
		OPERATION_FAIL	= -1,
		INVALID_SIZE	= -2,
		INVALID_DATA	= -3,
		TIMEOUT_ERR		= -200
	};

	class DataBase {
		public:
			DataBase(std::string);
			int init();
			//int insertEntry(const std::vector<char>& dataVec);
            DB::opStatus_t insertEntry(const std::shared_ptr<Student> student);
			int deleteEntry(int entryNumber);
            std::vector<char> readEntry(const std::string& id);

		private:
			std::string dbFileName;
			int entryCount;
	};
};
