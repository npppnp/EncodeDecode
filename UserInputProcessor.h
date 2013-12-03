#pragma once
#include "stdafx.h"
#include "Data.h"
#include "string.h"
#include <string>
#include "DataProcessor.h"
using namespace System;
//Types of operations user can perform
enum UserOperationMenuSelected{ Encode=1, Decode=2, exitFromOperation=3};
//Types of input data Sformats
enum UserInputTypeMenuSelected{ Return=0, Hex, Dec,  File, exitFromDataType};
/*
Descrption: This class defines functions to interact with end user for input/output 
and validates and processes
user input.
*/
class UserInputProcessor{
//Public methods of the class
public:
	//Default consutructor
	UserInputProcessor();
	//Default desutructor
	~UserInputProcessor();
	//Displays menu for user selection and validate and process the user input
	int GetAndExtractUserInput(int&);

//Prvaite methods of the class
private:
	//Called by GetAndExtractUserInput to check if file exists 
	//when user selected file as input
	int IsInputAValidFile(std::string strUserInput, std::string &strFileData,int &iInputDta);
	//Displays options for encoding, decoding and exit to user 
	//and process the selection
	int GetUserOperationMenuSelection();
	//Displays options for the format of input data for encoding, decoding, return 
	//and exit and process the selection
	int GetUserInputTypeMenuSelection(bool);
	//Gets name of file or hex or decimal input from user
	std::string GetDataFromUser();
	//Instance of DataProcessor class used to further process the user input
	//based on operation selected and data entered
	DataProcessor *m_ptrDataProcessor;
	
};

