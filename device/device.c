//************************** DEVICE MANAGEMENT SYSTEM **************************
//  Copyright (c) 2025 Trenser Technology Solutions
//  All Rights Reserved
//******************************************************************************
//
// File		: device.c
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
#include <stdlib.h>
#include <string.h>
#include "device.h"
#include "customTypes.h"
#include "file.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************
#define SUCCESS      (1)
#define WRITE_COUNT  (1)
#define READ_COUNT   (1)
#define CHAR_SIZE    (sizeof(char))
#define INT_SIZE     (sizeof(int))
#define LONG_SIZE     (sizeof(unsigned long))

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To add a new device to the entry
//Inputs	: File to be updated
//Outputs	: Updated file
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: File opened in append mode
//******************************************************************************
bool deviceAdd(const uint8 *pucFileName)
{
	bool blReturn = false;
	bool blResult = false;
	DEVICE_DETAILS DeviceData = {0};
	FILE *pstFile = NULL;
	DeviceData.pucDevName = NULL;
	DeviceData.pucDevType = NULL;
	uint32 ulLen = 0;
	uint8 ucNameLen = 0;
	uint8 ucTypeLen = 0;

	if (pucFileName != NULL)
	{
		pstFile = fileOpen(pucFileName, FILE_APPEND_MODE);
		if(pstFile != NULL)
		{
			printf("\nAdd device\n");
			printf("-----------------------------\n");
			getchar();
			printf("Enter the device name : ");
			getline((char **)&DeviceData.pucDevName, &ulLen, stdin);
			DeviceData.pucDevName[strcspn(DeviceData.pucDevName, "\n")] = '\0';
			ulLen = 0;
			printf("Enter the device type : ");
			getline((char **)&DeviceData.pucDevType, &ulLen, stdin);
			DeviceData.pucDevType[strcspn(DeviceData.pucDevType, "\n")] = '\0';
			ucNameLen = strlen((char *)DeviceData.pucDevName);
			ucTypeLen = strlen((char *)DeviceData.pucDevType);
			printf("Enter the device Id : ");
			scanf("%x", (unsigned int *)&DeviceData.ulDevId);
			printf("Enter the device vendor : ");
			scanf("%x", (unsigned int *)&DeviceData.ulDevVendor);
			printf("Enter the device Serial : ");
			scanf("%lu", &DeviceData.ulDevSerial);
			blResult = fileWrite(&ucNameLen, INT_SIZE, WRITE_COUNT, pstFile);
			blResult = fileWrite(DeviceData.pucDevName, CHAR_SIZE, ucNameLen,
									pstFile);
			blResult = fileWrite(&ucTypeLen, INT_SIZE, WRITE_COUNT, pstFile);
			blResult = fileWrite(DeviceData.pucDevType, CHAR_SIZE, ucTypeLen,
									pstFile);
			blResult = fileWrite(&DeviceData.ulDevId, INT_SIZE, WRITE_COUNT,
								 	pstFile);
			blResult = fileWrite(&DeviceData.ulDevVendor, INT_SIZE, WRITE_COUNT,
								 	pstFile);
			blResult = fileWrite(&DeviceData.ulDevSerial, LONG_SIZE, WRITE_COUNT,
								 	pstFile);
			blResult = fileClose(pstFile);
			if (blResult != blReturn)
			{
				blReturn = blResult;
			}
		}
		else
		{
			printf("\nUnable to add a new device : Failed to open the file");
		}
	}
	else
	{
		printf("\nUnable to add a new device : Missing file name");
	}
	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To list devices in file
//Inputs	: File name with device details
//Outputs	: None
//Return	: True, at time of successfull execution
//Return	: False, in case of an error
//Notes		: File opened in read mode
//******************************************************************************
bool deviceList(const uint8 *pucFileName)
{
	bool blReturn = false;
	DEVICE_DETAILS DeviceData = {0};
	FILE *pstFile = NULL;
	// char *name = NULL;
	// char *type = NULL;
	// size_t len = 0;
	DeviceData.pucDevName = NULL;
	DeviceData.pucDevType = NULL;
	uint32 ulLen = 0;
	uint8 ucNameLen = 0;
	uint8 ucTypeLen = 0;
	
	if (pucFileName != NULL)
	{
		pstFile = fileOpen(pucFileName, FILE_READ_MODE);
		if (pstFile != NULL)
		{
			printf("\nList device\n");
			printf("-----------------------------\n");
			printf("Name\tType\tId\tVendor\tSerial\n");
			while (1) 
			{
				if (fread(&DeviceData.ulDevId, sizeof(DeviceData.ulDevId), READ_COUNT,
					pstFile) != SUCCESS)
				{
					break;
					printf("\nE1");
				}
				if (fread(&DeviceData.ulDevVendor, sizeof(DeviceData.ulDevVendor),
					READ_COUNT, pstFile) != SUCCESS)
				{
					printf("\nE2");
					break;
				}
				if (fread(&DeviceData.ulDevSerial, sizeof(DeviceData.ulDevSerial),
					READ_COUNT, pstFile) != SUCCESS)
				{
					printf("\nE3");
					break;
				}
				if (fread(&ucNameLen, sizeof(ucNameLen), READ_COUNT,
					pstFile) != SUCCESS)
				{
					printf("\nE4");
					break;
				}
				DeviceData.pucDevName = malloc(ucNameLen + 1);
				fread(DeviceData.pucDevName, CHAR_SIZE, ucNameLen, pstFile);
				DeviceData.pucDevName[ucNameLen] = '\0';
				if (fread(&ucTypeLen, sizeof(ucTypeLen), READ_COUNT,
					pstFile) != SUCCESS)
				{
					printf("\nE5");
					break;
				}
				DeviceData.pucDevType = malloc(ucTypeLen + 1);
				fread(DeviceData.pucDevType, CHAR_SIZE, ucTypeLen, pstFile);
				DeviceData.pucDevType[ucTypeLen] = '\0';
				printf("%hhn\t%hhn\t%u\t%d\t%ld\n",
						DeviceData.pucDevName, DeviceData.pucDevType,
						DeviceData.ulDevId, DeviceData.ulDevVendor,
						DeviceData.ulDevSerial);
			}
			fclose(pstFile);
		}
		else
		{
			printf("\nUnable to list device : Failed to open the file");
		}
	}
	else
	{
		printf("\nUnable to list device : Missing file name");
	}
	return true;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To search an item in device list
//Inputs	: The file with device details and device Id to be searched
//Outputs	: 
//Return	: True, at time of successfull execution
//Return	: False, in case of an error
//Notes		: 
//******************************************************************************
bool deviceSearch(const uint8 *pucFileName, uint8 ucId)
{
	bool bReturn = false;
	return bReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To remove an item from the device list
//Inputs	: The file with device details and device Id to be removed
//Outputs	: 
//Return	: True, at time of successfull execution
//Return	: False, in case of an error
//Notes		: 
//******************************************************************************
bool deviceRemove(const uint8 *pucFileName, uint8 ucId)
{
	bool bReturn = false;
	return bReturn;
}
// EOF