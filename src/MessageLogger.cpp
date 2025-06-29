/*********************************************************************************
* Copyright reserved from 2025                                                   *
* SOURCE:src/MesssageLogger.cpp                                                  *                       
* AUTHOR: ANKIT                                                                  *     
* DATE : 29-June-25                                                              *
* Description: This class provides a singleton logger that writes messages to a  *
* log file in the user's Downloads directory. It supports logging info and error *
* messages with timestamps. The log file is created if it does not exist, and    *
* messages are appended to it. The class handles platform-specific paths for     *
* Windows and Unix-like systems.                                                 *
* It uses a mutex to ensure thread safety when writing to the log file.          *
**********************************************************************************/
/*================================================================================
|    ID         |   DATE        |   AUTHOR     |   DESCRIPTION                   |
|================================================================================|
|    001        |   29-June-25  |   ANKIT      | Created MessageLogger class     |
|================================================================================|  
|================================================================================*/


#include "MessageLogger.h"


#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <shlobj.h>
#pragma comment(lib, "shell32.lib")
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <limits.h>
#endif  

MessageLogger::MessageLogger() {
    std::string logFilePath = getDownloadsPath() + "/crypto_log.txt";
    logFile.open(logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error opening log file: " << logFilePath << std::endl;
    }
}

MessageLogger::~MessageLogger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
MessageLogger& MessageLogger::getInstance() {
    static MessageLogger instance;
    return instance;
}

std::string MessageLogger::currentDateTime() {
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

std::string MessageLogger::getDownloadsPath() {
#if defined(_WIN32) || defined(_WIN64)
    char path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path))) {
        return std::string(path) + "\\Downloads";
    } else {
        return std::string();
    }
#else
    const char* homeDir = getenv("HOME");
    if (!homeDir) {
        homeDir = getpwuid(getuid())->pw_dir;
    }
    std::string downloadsPath = std::string(homeDir) + "/Downloads";
    struct stat st;
    if (stat(downloadsPath.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
        return downloadsPath;
    } else {
        return std::string();
    }
#endif
}

void MessageLogger::logInfo(const std::string& msg) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) {
        logFile << "[" << currentDateTime() << "] INFO: " << msg << std::endl;
    }
}

void MessageLogger::logError(const std::string& msg) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) {
        logFile << "[" << currentDateTime() << "] ERROR: " << msg << std::endl;
    }
}
// End of src/MessageLogger.cpp
