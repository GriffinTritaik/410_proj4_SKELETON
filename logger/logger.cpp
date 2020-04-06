#include "../includes/logger.h"
using namespace std;

Logger::Logger(std::string filename) {
	this->filename = filename;
}

/*
 * Ensure that all files are closed and all mutexes released
 */
Logger::~Logger() {
}

//open close and clear the log file
/*
 * This function is not completed. We need to actually clear the file.
 */
void Logger::clearlogfile() {
	myFile.open(filename, std::fstream::trunc);

	//close file
	if (myFile.is_open())
		myFile.close();
}

/*
 * This appears to be done.
 */
void Logger::log(std::string data) {
	myFile.open(filename, std::fstream::app);
	if (!myFile.is_open())
		return;

	std::string myline;

	myFile << data;

	//close file
	if (myFile.is_open())
		myFile.close();
}
