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
//Inputs	: const uint8 *pucFileName, name of the file name which contains the
//				device details
//Inputs	: const uint8 *pucMode, specifies the mode in which the file 
//				to be opened
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: None
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
//Inputs	: FILE *pstFile, pointer to the file to be closed
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
//Inputs	: const void *pData, pointer to the data which is 
//				to be written to the file
//Inputs	: uint32 ulDataSize, size of the data to be written to the file
//Inputs	: uint32 ulDataCount, number of elements to be written to the file
//Inputs	: FILE *pstFile, pointer to the file to which the data is written
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: None
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

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To read data from the file
//Inputs	: void *pData, pointer to the data in which the readed data is stored
//Inputs	: uint32 ulDataSize, size of the data to be read from the file
//Inputs	: uint32 ulDataCount, number of elements to be read from the file
//Inputs	: FILE *pstFile, pointer to the file to which the data is written
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: None
//******************************************************************************
bool fileRead(void *pData, uint32 ulDataSize, uint32 ulDataCount,
				FILE *pstFile)
{
	bool blReturn = false;
	uint32 ucResult = 0;

	if(pData != NULL)
	{
		if(ulDataSize !=0 && ulDataCount !=0)
		{
			ucResult = fread(pData,ulDataSize,ulDataCount,pstFile);
			
			if(ucResult == ulDataCount)
			{
				blReturn = true;
			}
		}
		else
		{
			printf("\nUnable to read from the file : Invalid data parameters");
		}

	}

	else
	{
		printf("\nUnable to read from the file : Invalid data");
	}

	return blReturn;
}
// EOF