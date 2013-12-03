#pragma once
#include"string.h"
#include <iostream>
using namespace System;
using namespace std;
/*
Descrption: This is a singleton class defines functions to crate a log file
with user specified name and log data in it.
*/
class DataLogger
{
//Public methods of the class
public:
	//Returns the only existing instance of the class, 
	//if no instance exist, creates one and returns
	static DataLogger* GetInstance();
	//Default desutructor
	~DataLogger();
	//Creates log file with user specified name
	int CreateLogFile(std::string strLogFileName);
	//Writes specified information to log file
	int AppendData(std::string strLogData);
private:
	//Handle to log file created
	FILE *m_FileHandle;
	//Pointer to the single instance of itself
	static DataLogger* m_ptrDataLogger;
	//Private constructor
	DataLogger();
};

