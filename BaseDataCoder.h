#pragma once
#define SIZE_OF_DATA 16
#define SIZE_OF_INPUT 14
#include "Data.h"
/*This class outlines the member variables and functions required by Encoder/Decoder
classes and acts as base class them*/
class BaseDataCoder
{
//Public methods of the class
public:
	//Default consutructor
	BaseDataCoder();
	//Validates user input to be within range of possible
	//data which can be encoded or decoded
	int ValidateDataForRange(int);
	//Pure virtual function which will be implemented by derived classes
	//for data encoding or decoding
	virtual int EncodeDecodeData(int iData)=0;

//Members of base class which can be accessed by derived classes
protected:
	//minimum range value 
	int m_iMinValue;
	//maximum range value 
	int m_iMaxValue;
	//Size of data in bits, 14 in current case
	int m_iSizeOfData;
	//offset to be added to data when encoding and subtracted when decoding
	int m_iOffset;
private:
	
};

