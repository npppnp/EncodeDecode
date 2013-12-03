#include "stdafx.h"
#include "DataProcessor.h"
#include "Data.h"
#include "UserInputProcessor.h"
#include <sstream>
DataProcessor* DataProcessor::m_ptrDataProcess;
DataProcessor::DataProcessor()
{
	m_ptrDataLogger = DataLogger::GetInstance();
	
}
DataProcessor* DataProcessor::GetInstance()
{
	if (m_ptrDataProcess == NULL)
		m_ptrDataProcess = new DataProcessor();

	return m_ptrDataProcess;
}
int DataProcessor::ProcessData(int iData, int iDataType, int iOperation)
{
	int iProcessDataResult = Error;
	BaseDataCoder *ptrDataCoder = NULL;
	int iIsDataValid;
	std::string strLogOperation;
	if (iOperation == Encode)
	{
		DataEncoder *ptrEncoder = new DataEncoder();
		ptrDataCoder = (BaseDataCoder*)ptrEncoder;
	}
	else
	{
		DataDecoder *ptrDecoder = new DataDecoder();
		ptrDataCoder = (BaseDataCoder*)ptrDecoder;
	}
	if (ptrDataCoder != NULL)
	{
		iProcessDataResult = EncodeDecode(iDataType, iOperation, iData, ptrDataCoder);
		delete(ptrDataCoder);
	}
	
	return iProcessDataResult;
}
int DataProcessor::EncodeDecode(int iDataType, int iOperationType, int iInputData, BaseDataCoder *ptrDataCoder)
{
	int iEncodeDecodeResult = Error;
	int iIsDataValid;
	std::string strLogDataType, strLogOperation;
	std::stringstream ssWriteData;
	if (iDataType == Dec)
		strLogDataType = "\n Input Data Decimal format ";
	else
		strLogDataType = "\n Input Data HexaDecimal format ";
	if (iOperationType == Encode)
		strLogOperation = " Encoded Value ";
	else
		strLogOperation = " Decoded Value ";
	
	if (ptrDataCoder->ValidateDataForRange(iInputData) == Success)
	{
		short iEncodedData = ptrDataCoder->EncodeDecodeData(iInputData);

		ssWriteData << strLogDataType;
		if (iDataType == Hex)
			ssWriteData << std::hex << iInputData;
		else
			ssWriteData << iInputData;

		ssWriteData << strLogOperation << std::hex << iEncodedData;

		if (m_ptrDataLogger != NULL)
		{
			if (m_ptrDataLogger->AppendData(ssWriteData.str()) != Success)
				printf("\n error writing data to log file");
		}
		iEncodeDecodeResult = Success;

	}
	else
		iEncodeDecodeResult = OutOfRangeInput;
	return iEncodeDecodeResult;
	
}
int DataProcessor::IsInputAValidInteger(std::string strUserInput, int &iInputData)
{
	int iInputValidIntegerResult = Error;

	if (strUserInput.find_first_not_of("-0123456789") != std::string::npos)
		iInputValidIntegerResult = InvalidUnserInput;
	else
	{
		int iInput = std::stoi(strUserInput, 0, 10);
		iInputData = iInput;
		iInputValidIntegerResult = Success;
		std::cout << "\n user input converted to " << iInputData;
	}

	return iInputValidIntegerResult;
}
int DataProcessor::IsInputAValidHexadecimal(std::string strUserInput, int &iInputData)
{
	int iInputValidHexResult = Error;

	if (strUserInput.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
	{
		iInputValidHexResult = InvalidUnserInput;

	}
	else
	{

		int iInput = std::stoi(strUserInput, 0, 16);
		iInputData = iInput;
		iInputValidHexResult = Success;
		printf("\n user input dec value %d ", iInputData);
	}
	return iInputValidHexResult;
}
int DataProcessor::ProcessData(std::string strInputData, int iDataType, int iOperation)
{
	int iProcessDataResult = Error;
	int iStartOfNewData = 0, iStartOfSubstring = 0, iSizeOfFileData, iSizeOfData, iInputData;
	bool flgEndOfData = false;
	std::string strData, strLogOperation, strLogDataType;
	
	BaseDataCoder *ptrDataCoder = NULL;
	int iIsDataValid;
	iSizeOfFileData = strInputData.size();
	if (iOperation == Encode)
	{
		DataEncoder *ptrEncoder = new DataEncoder();
		ptrDataCoder = (BaseDataCoder*)ptrEncoder;
		strLogOperation = " Encoded Value ";
	}
	else
	{
		DataDecoder *ptrDecoder = new DataDecoder();
		ptrDataCoder = (BaseDataCoder*)ptrDecoder;
		strLogOperation = " Decoded Value ";
	}
	if (ptrDataCoder != NULL)
	{

		while (!flgEndOfData)
		{
			std::stringstream ssWriteData;
			iStartOfNewData = strInputData.find(" ", (size_t)iStartOfSubstring);

			if (iStartOfNewData == string::npos)
			{
				iSizeOfData = strInputData.size();
				flgEndOfData = true;
			}
			else
				iSizeOfData = iStartOfNewData - iStartOfSubstring;
			strData = strInputData.substr(iStartOfSubstring, iSizeOfData);
			cout << "\n processing file substring " << strData;
			
			iStartOfNewData++;
			if (iDataType == Dec)
			{
				iIsDataValid = IsInputAValidInteger(strData, iInputData);
				strLogDataType = "\n File Input Data Decimal format ";
			}
			else
			{
				iIsDataValid = IsInputAValidHexadecimal(strData, iInputData);
				strLogDataType = "\n File Input Data HexaDecimal format ";
			}
			if (iIsDataValid == Success)
			{
				cout << "\n int value for substring to process" << iInputData;
				iProcessDataResult = EncodeDecode(iDataType, iOperation, iInputData, ptrDataCoder);
			}
			iStartOfSubstring = iStartOfNewData;
		}
		delete(ptrDataCoder);
	}
	return iProcessDataResult;

}
DataProcessor::~DataProcessor()
{
}
