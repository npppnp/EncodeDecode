#include "stdafx.h"
#include "DataDecoder.h"
#include "DataEncoder.h"
#include "Data.h"
#include <iostream>
DataDecoder::DataDecoder()
{
	m_iMinValue = 0;
	m_iOffset = (pow(2, SIZE_OF_INPUT)) / 2;//offset to be subtracted
	m_iNoOfBitsOfMSBToLSB = (SIZE_OF_DATA - SIZE_OF_INPUT) / 2;//No of bit of Most Significant Byte to be moved to LSB
	DataEncoder *ptrEncoder = new DataEncoder();
	int iTempDataToEncode = (0xffff >> (SIZE_OF_DATA - SIZE_OF_INPUT + 1));
	m_iMaxValue = ptrEncoder->EncodeDecodeData(iTempDataToEncode);
}

int DataDecoder::EncodeDecodeData(int iDataToBeDecoded)
{
	int iDecodedData;
	short iDataMSB = iDataToBeDecoded&MSB_MASK;
	iDataMSB >>= m_iNoOfBitsOfMSBToLSB;
	iDataToBeDecoded &= ~MSB_MASK;
	iDecodedData = iDataMSB|iDataToBeDecoded;
	iDecodedData -= m_iOffset;
	return iDecodedData;
}
DataDecoder::~DataDecoder()
{
}
