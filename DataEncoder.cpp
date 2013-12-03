#include "stdafx.h"
#include "DataEncoder.h"
#include "stdio.h"
#include <iostream>
#include "Data.h"
DataEncoder::DataEncoder()
{
	m_iOffset = 0x0001<<(SIZE_OF_INPUT-1);//offset to be added
	m_iNoOfBitsToBeMasked = (SIZE_OF_DATA - SIZE_OF_INPUT) / 2;//No of bit of MSB and LSB to be masked
	m_iMaskLSB = ~(0xfffe << ((SIZE_OF_INPUT / 2) - 1));//Mask to reset Most Significant bits of LSB
	m_iMaskMSB = m_iMaskLSB << 8;//Mask to reset Most Significant bits of MSB
	m_iMaxValue = 0xffff >> (SIZE_OF_DATA - SIZE_OF_INPUT + 1);
	m_iMinValue = ~m_iMaxValue;
}

int DataEncoder::EncodeDecodeData(int iData)
{
	int iEncodedData;
	int iEncodedDataTemp = iData + m_iOffset;//add the offset
	iEncodedData = iEncodedDataTemp << m_iNoOfBitsToBeMasked;//Move of the bit/bits of LSB which are to be masked to MSB
	iEncodedDataTemp &= m_iMaskLSB;//Mask most signigicant bit/bits of LSB of offsetted data
	iEncodedData &= m_iMaskMSB;//Mask most signigicant bit/bits of MSB of offsetted data
	iEncodedData |= iEncodedDataTemp;//combine LSB and MSB of encoded data
	return iEncodedData;
}

