#pragma once
#include "BaseDataCoder.h"
#define MSB_MASK 0xff00
/*This class is derived from BaseDataCoder and assigns the member variables
and define functions required for decoding of data*/
class DataDecoder:public BaseDataCoder
{
//Public methods of the class
public:
	//Default consutructor, initializes the meber variables required for 
	//data decoding
	DataDecoder();
	~DataDecoder();
	//Actual algorithm to decode data
	int EncodeDecodeData(int);
	
private:
	//No bits to be moved back from MSB to LSB while decoding
	short m_iNoOfBitsOfMSBToLSB;
	
};

