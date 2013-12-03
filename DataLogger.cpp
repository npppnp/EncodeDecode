#include "stdafx.h"
#include "DataLogger.h"
#include "Data.h"
DataLogger* DataLogger::m_ptrDataLogger;
DataLogger::DataLogger()
{
}
DataLogger* DataLogger::GetInstance()
{
	if (m_ptrDataLogger == NULL)
		m_ptrDataLogger = new DataLogger();
	return m_ptrDataLogger;
}
int DataLogger::CreateLogFile(std::string strLogFileName)
{
	int iDataLoggerCreation = Success;
	m_FileHandle = fopen(strLogFileName.c_str(), "w");
	char *strFileData;
	if (m_FileHandle == NULL)
		iDataLoggerCreation = DataLoggerError;
		
	return iDataLoggerCreation;
}
int DataLogger::AppendData(string strData)
{
	int iDataWriteError;
	fputs(strData.c_str(), m_FileHandle);
	if (ferror(m_FileHandle) != 0)
		iDataWriteError = DataLoggerError;
	else
		iDataWriteError = Success;
	return iDataWriteError;
}
DataLogger::~DataLogger()
{
	fclose(m_FileHandle);
}
