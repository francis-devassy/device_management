//************************** DEVICE MANAGEMENT SYSTEM **************************
//  Copyright (c) 2025 Trenser Technology Solutions
//  All Rights Reserved
//******************************************************************************
//
// File		: file.c
// Summary	: Options to update device data history
// Note		: Feature to add, list, search and remove devices to the data 
//			  history
// Author	: Francis V D
// Date		: 24-December-2025
//
//******************************************************************************

//******************************* Include Files ********************************
#include <stdio.h>
#include <stdbool.h>
#include "customTypes.h"
//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: Opens the file
//Inputs	: Mode and name of the file to be opned
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: 
//******************************************************************************
FILE* fileOpen(const uint8 *pucFileName, const uint8 *pucMode)
{
	FILE *pstFile = NULL;

	if(pucFileName != NULL)
	{
		if(pucMode != NULL)
		{
			pstFile = fopen((const char *)pucFileName, (const char *)pucMode);
			if(pstFile == NULL)
			{
				printf("\n Unable to open the file");
			}
		}
		else
		{
			printf("\n File mode missing, file not opened");
		}
	}
	else
	{
		printf("\n File name missing, file not opened");
	}
	return pstFile;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: Close the file
//Inputs	: Pointer to the file to be closed
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: 
//******************************************************************************
bool fileClose(FILE *pstFile)
{
	bool blReturn = false;
	int8 cResult = 0;

	if(pstFile != NULL)
	{
		cResult = fclose(pstFile);
		if(cResult == 0)
		{
			blReturn = true;
		}
		else
		{
			printf("\nFailed to close the file");
		}
	}
	else
	{
		printf("\nUnable to close the file : Invalid file");
	}
	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To write data to the file
//Inputs	: Data to be written and pointer to the file
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: 
//******************************************************************************
bool fileWrite(const void *pData, uint32 ulDataSize, uint32 ulDataCount,
				FILE *pstFile)
{
	bool blReturn = false;
	uint32 ucResult = 0;

	if(pData != NULL)
	{
		if(ulDataSize !=0 && ulDataCount !=0)
		{
			ucResult = fwrite(pData,ulDataSize,ulDataCount,pstFile);
			if(ucResult == ulDataCount)
			{
				blReturn = true;
			}
			else
			{
				printf("\nUnable to write to the file : Write error");
			}
		}
		else
		{
			printf("\nUnable to write to the file : Invalid data parameters");
		}

	}
	else
	{
		printf("\nUnable to write to the file : Invalid data");
	}
	return blReturn;
}
// EOF