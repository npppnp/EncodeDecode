#pragma once
#include <iostream>
#include "DataDecoder.h"
#pragma once
#include "DataEncoder.h"
#include "DataLogger.h"

//Singleton class which processes all sorts of Data, viz. Hex, Decimal and filestream
//for encoding and decoding and log it in logfile COnvertedData.txt
class DataProcessor
{
//Public methods of the class
public:
	//Default desutructor
	~DataProcessor();
	//Returns the only existing instance of the class, 
	//if no instance exist, creates one and returns
	static DataProcessor* GetInstance();
	//Process Hex or Decimal data for encoding/decoding
	int ProcessData(int,int,int);
	//Process string data for encoding/decoding
	//Used to process file data, treats each element
	//separated by " " in the string as a different hex/decimal 
	//number to be processed
	int ProcessData(std::string, int,int);
	//Validates if the string contains only decimal integer data,
	//if yes, outputs equivalent integer else return error
	int IsInputAValidInteger(std::string,int&);
	//Validates if the string contains only hexadecimal integer data,
	//if yes, outputs equivalent integer else return error
	int IsInputAValidHexadecimal(std::string,int&);
private:
	//Private constructor
	DataProcessor();
	//Encodes/decodes the passed integer value using BaseDataCoder
	//Data type and operation type passed are used for writing correct 
	//information in log file
	int EncodeDecode(int, int,int,BaseDataCoder *);
	//Pointer to the single instance of itself
	static DataProcessor* m_ptrDataProcess;
	//Pointer to the DataLogger to log the encoded/decoded values
	DataLogger* m_ptrDataLogger;

};

