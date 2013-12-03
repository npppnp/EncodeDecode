// Pratibha_Pandhare_Part1.cpp : main project file.

#include "stdafx.h"
#include "stdio.h"
#include "UserInputProcessor.h"
#include "DataEncoder.h"
#include "DataDecoder.h"
#include "DataLogger.h"
#include <iostream>
#include <sstream>
using namespace System;
using namespace std;

#define INPUT_DATA_SIZE 14//Using this macro, size of input data can be changed
#define CHECK_WITH_USER_FOR_MORE_OPERATIONS char chSelection; std::cout<<"\n\n Do you want to perform more operations? Hit Y for yes, N to exit."; std::cin>>chSelection; if((chSelection == 'N')||(chSelection == 'n')) break; else continue;

DataLogger *ptrLogger= NULL;
UserInputProcessor *userInputProcessor;

int main(int argc, char *args[])
{
	int iMinInput, iMaxInput,iOffsetValue;
	try
	{
		//Initiate UserInputProcessor instance in order to take input from user
		userInputProcessor = new UserInputProcessor();
		//Instantiate DataLogger and create Log fle
		ptrLogger = DataLogger::GetInstance();
		int iLogFileCreationResult = ptrLogger->CreateLogFile("ConvertedData.txt");
		
		if (userInputProcessor != NULL)
		{
			int iUserInputProcessResults, iInputData, iTypeOfOperation = Encode, iUserInputType;
			std::string strInputData;
			
			//keep checking with user for operation to be performed(encode/decode) till user selects to Exit
			while (iTypeOfOperation != Exit)
			{

				iUserInputProcessResults = userInputProcessor->GetAndExtractUserInput(iTypeOfOperation);
				//If user has opted to exit from an operation or any other menu, break the loop and exit the application
				if ((iTypeOfOperation == exitFromOperation) || (iUserInputProcessResults == Exit))
					break;						
				else if (iUserInputProcessResults == InvalidUnserInput)//Notify invalid selection and prompt for reselection
					printf("\n user entered invalid input, error code : %d ", iUserInputProcessResults);
				CHECK_WITH_USER_FOR_MORE_OPERATIONS;
			}

			
		}
		if (userInputProcessor != NULL)
			delete(userInputProcessor);
		if (ptrLogger != NULL)
			delete(ptrLogger);
	}
	catch (exception occuredException)
	{ 
		printf("\n Exception %x occurred! ", occuredException.what());
		if (userInputProcessor != NULL)
			delete(userInputProcessor);
		if (ptrLogger != NULL)
			delete(ptrLogger);
	}
    return 0;
}
