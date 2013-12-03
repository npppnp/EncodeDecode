#include "stdafx.h"
#include "UserInputProcessor.h"
#include "stdio.h"
#include <string>
#include <iostream>
#define DISPLAY_INVALID_SELECTION std::cout<<"\n Error! Invalid Selection, please choose any of the following valid entries!"

UserInputProcessor::UserInputProcessor()
{
	m_ptrDataProcessor = DataProcessor::GetInstance();
}
UserInputProcessor::~UserInputProcessor()
{
	delete(m_ptrDataProcessor);
}
std::string UserInputProcessor::GetDataFromUser()
{
	std::string strUserInput; 
	std::cout << "Enter the value : "; 
	std::cin >> strUserInput;
	return strUserInput;
}
int UserInputProcessor::GetUserOperationMenuSelection()
{
	int iUserOperationSelection;
	std::cout << "\n Please select operation to be Performed :";
	std::cout << "\n 1. Hit 1 for data Encoding";
	std::cout << "\n 2. Hit 2 for data Decoding";
	std::cout << "\n 3. Hit 3 to Exit\n";
	std::cin>>iUserOperationSelection;
	
	switch (iUserOperationSelection)
	{
	case Encode:
	case Decode:
	case exitFromOperation:
		break;
	default:
		DISPLAY_INVALID_SELECTION;
		iUserOperationSelection = GetUserOperationMenuSelection();
		break;
	}
	return iUserOperationSelection;
}
int UserInputProcessor::GetUserInputTypeMenuSelection(bool flgForFileData)
{
	int iUserInputTypeSelection;
	std::cout << "\n Please select the data input format :";
	std::cout << "\n 0. Hit 0 to return to main menu";
	std::cout << "\n 1. Hit 1 to enter Hexadecimal input";
	std::cout << "\n 2. Hit 2 to enter Decimal input ";
	if (!flgForFileData)
		std::cout << "\n 3. Hit 3 to enter input file name";
	std::cout << "\n 4. Hit 4 to Exit \n";
	std::cin >> iUserInputTypeSelection;
	switch (iUserInputTypeSelection)
	{
	case Hex:
	case Dec:
	case Return:
		break;
	case File:
		if (flgForFileData)
		{
			DISPLAY_INVALID_SELECTION;
			iUserInputTypeSelection = GetUserInputTypeMenuSelection(flgForFileData);
		}
	case exitFromDataType:
		break;
	
	default:
		DISPLAY_INVALID_SELECTION;
		iUserInputTypeSelection = GetUserInputTypeMenuSelection(flgForFileData);
		break;
	}
	return iUserInputTypeSelection;
}
int UserInputProcessor::GetAndExtractUserInput(int &iTypeOfOperation)
{
	int iValidateUserInputResults = Error;
	int iInputData, iUserInputType;
	std::string strInputString;
	
	std::string strFileName;
	OperationSelection:
	iTypeOfOperation = GetUserOperationMenuSelection();
	if ((iTypeOfOperation == Encode) || (iTypeOfOperation == Decode))
	{
		iUserInputType = GetUserInputTypeMenuSelection(false);
		switch (iUserInputType)
		{
		case Hex:
			strInputString = GetDataFromUser();
			iValidateUserInputResults = m_ptrDataProcessor->IsInputAValidHexadecimal(strInputString, iInputData);
			m_ptrDataProcessor->ProcessData(iInputData, iUserInputType, iTypeOfOperation);
			break;
		case Dec:
			strInputString = GetDataFromUser();
			iValidateUserInputResults = m_ptrDataProcessor->IsInputAValidInteger(strInputString, iInputData);
			m_ptrDataProcessor->ProcessData(iInputData, iUserInputType, iTypeOfOperation);
			break;
		case File:
			
			strFileName = GetDataFromUser();
			iUserInputType = GetUserInputTypeMenuSelection(true);
			iValidateUserInputResults = IsInputAValidFile(strFileName, strInputString, iInputData);
			m_ptrDataProcessor->ProcessData(strInputString, iUserInputType, iTypeOfOperation);
			break;
		case Return:
			goto OperationSelection;
		case exitFromDataType:
			break;
		default:
			iValidateUserInputResults = InvalidUnserInput;
			break;
		}
	}
	else if(iTypeOfOperation == exitFromOperation)
		iValidateUserInputResults = Exit;
	return iValidateUserInputResults;
}
int UserInputProcessor::IsInputAValidFile(std::string strUserInput, std::string &strFileData,int &iInputData)
{
	int iInputValidFileResult = Error;
	
	FILE *FileHandle;
	
	FileHandle = fopen(strUserInput.c_str(), "r");
	int iErrorNo;
		
		
	int iNoOfBytesToBeRead, iNoOfBytesRead;
	if (FileHandle != NULL)
	{
		iInputValidFileResult = Success;
		fseek(FileHandle, 0, SEEK_END);
		iNoOfBytesToBeRead = ftell(FileHandle);
		rewind(FileHandle);
		strFileData.resize(iNoOfBytesToBeRead);
		iNoOfBytesRead = fread((void*)strFileData.c_str(), 1, iNoOfBytesToBeRead, FileHandle);
			
		fclose(FileHandle);
		int iEndOfData;
						
	}
	else
	{
		_get_errno(&iErrorNo);
		printf("\n file open error %d", iErrorNo);
		iInputValidFileResult = InputFileDoesNotExist;
	}
	
	return iInputValidFileResult;
}
