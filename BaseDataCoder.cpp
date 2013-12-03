#include "stdafx.h"
#include "BaseDataCoder.h"


BaseDataCoder::BaseDataCoder()
{
	
}
int BaseDataCoder::ValidateDataForRange(int iDataToBeDecoded)
{
	int iInputValidIntegerResult;
	if ((iDataToBeDecoded < m_iMinValue) || (iDataToBeDecoded > m_iMaxValue))
		iInputValidIntegerResult = OutOfRangeInput;
	else
		iInputValidIntegerResult = Success;
	return iInputValidIntegerResult;
}