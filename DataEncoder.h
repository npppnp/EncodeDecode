#pragma once
#include "BaseDataCoder.h"
/*This class is derived from BaseDataCoder and assigns the member variables 
and define functions required for encoding of data*/
class DataEncoder:BaseDataCoder
{
	//Public methods of the class
public:
	//Default consutructor, initializes the meber variables required for 
	//data encoding
	DataEncoder();
	~DataEncoder();
	//Actual algorithm to encode data
	int EncodeDecodeData(int);
	
private:
	//No if bits of LSB and MSB to be resetted
	short m_iNoOfBitsToBeMasked;
	//Mask to reset LSB bit
	short m_iMaskLSB;
	//Mask to reset MSB bit
	short m_iMaskMSB;
};

