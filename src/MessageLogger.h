/*********************************************************************************
* Copyright reserved from 2025                                                   *
* SOURCE:src/MesssageLogger.h                                                    *                       
* AUTHOR: ANKIT                                                                  *     
* DATE : 29-June-25                                                              *
**********************************************************************************/
/*================================================================================
|    ID         |   DATE        |   AUTHOR     |   DESCRIPTION                   |
|================================================================================|
|    001        |   29-June-25  |   ANKIT      | Created MessageLogger class     |
|================================================================================|  
==================================================================================*/


#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <ctime>
#include <cstdlib>
#include <sstream>

class MessageLogger {
public:
    static MessageLogger& getInstance();

    void logInfo(const std::string& msg);
    void logError(const std::string& msg);

private:
    MessageLogger();
    ~MessageLogger();
    MessageLogger(const MessageLogger&) = delete;
    MessageLogger& operator=(const MessageLogger&) = delete;

    std::ofstream logFile;
    std::mutex logMutex;

    std::string currentDateTime();
    std::string getDownloadsPath();
};