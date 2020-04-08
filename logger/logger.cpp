/*
 * logger.cpp
 *
 * Henry R. Wilson and Griffin P. Tritaik
 *
 * 2020-04
 */

#include "../includes/logger.h"

//using namespace std;
//Henry Wilson hates this

Logger::Logger(std::string filename) {
	this->filename = filename;
}

/*
 * Ensure that all files are closed and all mutexes released
 */
Logger::~Logger() {
	//Should never be true at this point, but just to check...
	if(myFile.is_open()){
		myFile.close();
	}
	//Not releasing m (mutex), as is ONLY used with std::lock_guard.
	//Raw mutices are not safe.
}

//open close and clear the log file
/*
 * threadsafe due to explicitly scoped lock_guard
 */
void Logger::clearlogfile() {
	//makes section thread-safe
    {
    std::lock_guard<std::mutex> lock(m);

	//Turns out this truncate flag does all the work for us
	myFile.open(filename, std::fstream::trunc);

	//close file
	if (myFile.is_open()){
		myFile.close();
	}
    }
}

/*
 * Threadsafe due to explicitly scoped lock_guard
 */
void Logger::log(std::string data) {

	{
    std::lock_guard<std::mutex> lock(m);

	myFile.open(filename, std::fstream::app);
	if (!myFile.is_open()){
		return;
	}

	std::string myline;

	myFile << data;

	//close file
	if (myFile.is_open()){
		myFile.close();
	}
	}
}
