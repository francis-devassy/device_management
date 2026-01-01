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
#include "menu.h"
#include "constants.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************
#define PRINT_ERROR			(-1)
#define WRITE_COUNT			(1)
#define READ_COUNT			(1)
#define CHAR_SIZE			(sizeof(char))
#define INT_SIZE			(sizeof(int))
#define LONG_SIZE			(sizeof(unsigned long))
#define VALUE_ONE			(1)
#define READ_HEX			(1)
#define READ_NON_HEX		(0)
#define STRINGS_EQUAL		(0)
#define PRINT_ENABLED		(1)
#define PRINT_DISABLED		(0)
#define TEMPORARY_FILE_NAME	("temporary.dat")
#define ARRAY_SIZE			(100)
#define INCREMENT_BY_ONE	(1)

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: Check whether the Serial number is already exist in device data
//Inputs	: uint32 *pulSerial, the Serial value to be checked whether it 
//				already used
//Outputs	: None
//Return	: True, if the Serial number has not already been used
//Return	: False, if the Serial number has already been used
//Notes		: None
//******************************************************************************
static bool deviceCheckSerialAvailable(uint32 pulSerial,
										const uint8 *pucFileName)
{
	bool blReturn = true;
	DEVICE_DETAILS DeviceData = {0};
	FILE *pstFile = NULL;

	if (pucFileName != NULL)
	{
		fileOpen(&pstFile, pucFileName, FILE_READ_MODE);
		
		if(pstFile != NULL)
		{
			while(fileRead(&DeviceData, sizeof(DeviceData),
							READ_COUNT, pstFile) == SUCCESS)
			{
				if(DeviceData.ulDeviceSerial == pulSerial)
				{
					printf("\nThe Serial number has already been used");
					blReturn = false;
				}
				
			}
		}
	}

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To print details of a device
//Inputs	: DEVICE_DETAILS DeviceData, the variable for the device of which 
//			  the details to be printed
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: 
//******************************************************************************
static bool devicePrintData(DEVICE_DETAILS *pDeviceData)
{
	bool blReturn = false;
	int8 cResult = 0;

	if(pDeviceData != NULL)
	{
		cResult = printf("%s\t\t%s\t\t0x%lX\t\t0x%lX\t\t%lu\n",
						pDeviceData->pucDeviceName,
						pDeviceData->pucDeviceType, pDeviceData->ulDeviceId,
						pDeviceData->ulDeviceVendor,
						pDeviceData->ulDeviceSerial);

		if(cResult > PRINT_ERROR)
		{
			blReturn = true;
		}
	}
	else
	{
		printf("\n Unable to print device data : Invalid DeviceData pointer");
	}

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To read value to a variable entered by the user
//Inputs	: const uint8 *pucStringInformation, string that describes the
//				detail of expected data as input
//Inputs	: uint32 *pulValue, variable to which the read data is stored
//Inputs	: bool blReadHex, used to check whether the value to be read in 
//				hex format or not
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: None
//******************************************************************************
static bool deviceReadValue(const uint8 *pucStringInformation,
							uint32 *pulValue, bool blReadHex)
{
	bool blReturn = false;

	if(pucStringInformation != NULL && pulValue != NULL &&
		(blReadHex == true || blReadHex == false))
	{

		printf("%s", pucStringInformation);

		if(blReadHex == READ_HEX)
		{
			blReturn = scanf("%lx",pulValue);
			menuFlushInput();
		}
		else
		{
			blReturn = scanf("%lu",pulValue);
			menuFlushInput();
		}

		if(blReturn != SUCCESS)
		{
			printf("\n Unable to read the value : Invalid input");
		}
	}
	else
	{
		printf("\n Unable to read the value : Invalid function arguments");
	}

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To read a string entered by the user 
//Inputs	: const uint8 *pucStringInformation, string that describes 
//			  expected input data
//Inputs	: uint8 *pucString, variable to store the string entered by the user
//			  input 
//Inputs	: uint32 ulSize, maximum number of bytes to be read
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: None
//******************************************************************************
static bool deviceReadString(const uint8 *pucStringInformation,
							uint8 *pucString, uint32 ulSize)
{
	bool blReturn = false;

	if(pucStringInformation != NULL && pucString != NULL && ulSize >= 0)
	{
		printf("%s", pucStringInformation);

		if(fgets((char *)pucString, ulSize, stdin) != NULL)
		{
			 if (strchr(pucString, '\n') == NULL)
			 {
				// New line missing in string, i.e user entered
				// more than 32 characters
				menuFlushInput();
			 }
			pucString[strcspn((char *)pucString, "\n")] = '\0';
			blReturn = true;
		}
		else
		{
			printf("\nUnable to read the string : Read process failed");
		}
		
		
	}
	else
	{
		printf("\n Unable to read the string : Invalid function arguments");
	}

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To read the device details provided by the user
//Inputs	: DEVICE_DETAILS *pstDeviceData, used to store the device details 
//				entered  by the user
//Inputs	: const uint8 *pucFileName, name of the file name which contains the
//				device details
//Outputs	: None
//Return	: True, if all the device details has been read properly
//Return	: False, if any error while reading the device details
//Notes		: None
//******************************************************************************
static bool deviceReadData(DEVICE_DETAILS *pstDeviceData,
							const uint8 *pucFileName)
{
	bool blReturn = false;

	blReturn = deviceReadString("Enter the device name : ",
								pstDeviceData->pucDeviceName, STR_MAX_SIZE);

	if(blReturn == SUCCESS)
	{
		blReturn =  deviceReadString("Enter the device type : ",
										pstDeviceData->pucDeviceType,
										STR_MAX_SIZE);
	}

	if(blReturn == SUCCESS)
	{
		blReturn = deviceReadValue("Enter the device Id : ",
									&pstDeviceData->ulDeviceId,
									READ_HEX);
	}

	if(blReturn == SUCCESS)
	{
		blReturn = deviceReadValue("Enter the device vendor : ",
									&pstDeviceData->ulDeviceVendor,
									READ_HEX);
	}

	if(blReturn == SUCCESS)
	{
		deviceReadValue("Enter the device Serial : ",
						&pstDeviceData->ulDeviceSerial, 
						READ_NON_HEX);
		blReturn = deviceCheckSerialAvailable(pstDeviceData->ulDeviceSerial,
												pucFileName);
	}

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To search device with matching string
//Inputs	: FILE *pstFile, pointer to the file which contains the device data
//Inputs	: uint32 ucChoice, the choice selected by user as search criteria
//Inputs	: const uint8 *pucStringToSearch, the string which is to be compared
//				among the existing device details
//Outputs	: None
//Return	: True, if a match is found
//Return	: False, in case no match found
//Notes		: None
//******************************************************************************
static bool deviceCheckStringMatch(FILE *pstFile,
									uint32 ucChoice,
									const uint8 *pucStringToSearch)
{
	bool blReturn = false;
	DEVICE_DETAILS DeviceData = {0};
	
	while(fileRead(&DeviceData, sizeof(DeviceData),
				  READ_COUNT, pstFile) == SUCCESS)
	{
		if(((ucChoice == SEARCH_BY_NAME) && 
			(strcmp((char*)DeviceData.pucDeviceName,
			pucStringToSearch) == STRINGS_EQUAL)) ||
			((ucChoice == SEARCH_BY_TYPE) && 
			(strcmp((char*)DeviceData.pucDeviceType,
			pucStringToSearch) == STRINGS_EQUAL)))
		{
			printf("Name\t\tType\t\tId\t\tVendor\t\tSerial\n");
			devicePrintData(&DeviceData);			
			blReturn = SUCCESS;
		}
	}

	if(blReturn != SUCCESS)
	{
		printf("No matching string found\n");
	}

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To search device with matching string
//Inputs	: FILE *pstFile, pointer to the file which contains the device data
//Inputs	: uint32 ucChoice, the choice selected by user as search criteria
//Inputs	: uint32 ulValueToSearch, the value which is to be compared
//				among the existing device details
//Outputs	: None
//Return	: True, if a match is found
//Return	: False, in case no match found
//Notes		: None
//******************************************************************************
static bool deviceCheckValueMatch(FILE *pstFile,
									uint32 ucChoice,
									uint32 ulValueToSearch)
{
	bool blReturn = false;
	DEVICE_DETAILS DeviceData = {0};
	
	while(fileRead(&DeviceData, sizeof(DeviceData),
				  READ_COUNT, pstFile) == SUCCESS)
	{
		if(((ucChoice == SEARCH_BY_ID) &&
			(DeviceData.ulDeviceId == ulValueToSearch)) ||
			((ucChoice == SEARCH_BY_VENDOR) &&
			(DeviceData.ulDeviceVendor == ulValueToSearch)) ||
			((ucChoice == SEARCH_BY_SERIAL) &&
			(DeviceData.ulDeviceSerial == ulValueToSearch)))
		{
			
			printf("Name\t\tType\t\tId\t\tVendor\t\tSerial\n");
			devicePrintData(&DeviceData);
			blReturn = SUCCESS;
		}
	}
	if(blReturn != SUCCESS)
	{
		printf("No matching value found");
	}

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To search device data based on criteria
//Inputs	: FILE *pstFile,  pointer to the file which contains the device data
//Inputs	: uint32 ucChoice, the choice selected by user as search criteria 
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: User will provide the data to be searched based on the selected
//				criteria
//******************************************************************************
static bool deviceSearchByCriteria(FILE *pstFile,
									uint32 ucChoice)
{
	bool blReturn = false;
	DEVICE_DETAILS DeviceData = {0};
	uint8 ucStringToSearch[STR_MAX_SIZE] = "";
	uint32 ulValueToSearch = 0;
	

	if(pstFile != NULL && 
		(ucChoice >= 0 && ucChoice <= SEARCH_CRITERIA_MAXIMUM_OPTIONS))
	{

		if(ucChoice == SEARCH_BY_NAME || ucChoice == SEARCH_BY_TYPE)
		{
			if(ucChoice == SEARCH_BY_NAME)
			{
				blReturn = deviceReadString("Enter Name: ",
										ucStringToSearch, STR_MAX_SIZE);
			}
			else
			{
				blReturn = deviceReadString("Enter Type: ",
										ucStringToSearch, STR_MAX_SIZE);			
			}

			if(blReturn == SUCCESS)
			{
				deviceCheckStringMatch(pstFile, ucChoice, ucStringToSearch);
			}
		}
		else if(ucChoice == SEARCH_BY_ID || ucChoice == SEARCH_BY_VENDOR ||
				ucChoice == SEARCH_BY_SERIAL)
		{
			if(ucChoice == SEARCH_BY_ID)
			{
				blReturn = deviceReadValue("Enter Id: ",
										&ulValueToSearch, READ_HEX);
			}
			else if(ucChoice == SEARCH_BY_SERIAL)
			{
				blReturn = deviceReadValue("Enter Serial: ",
										&ulValueToSearch, READ_NON_HEX);
			}
			else
			{
				blReturn = deviceReadValue("Enter Vendor: ",
										&ulValueToSearch, READ_HEX);
			}

			if(blReturn == SUCCESS)
			{
				deviceCheckValueMatch(pstFile, ucChoice, ulValueToSearch);
			}
			
		}
		else
		{
			printf("\nUnable to search : Invalid search criteria");
		}
	}
	else
	{
		printf("\nUnable to search by criteria : Invalid parameters");
	}

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To check how many times an item value is repeated in device data
//Inputs	: 
//Inputs	: 
//Outputs	: None
//Return	: Return the count the item repeated
//Notes		: None
//******************************************************************************
static uint8 deviceItemRepeatCount(uint8 ucChoice, 
									uint32 ulValueToCount,
									const uint8 *pucStringToCount,
									DEVICE_DETAILS *pMatchedDeviceData)
{
	uint8 ucRepeatCount = 0;
	uint8 ucIteration = 0;
	uint8 ucDeletionChoice = 0;
	DEVICE_DETAILS DeviceData = {0};
	FILE *pstFile = NULL;
	//DEVICE_DETAILS MatchedDeviceData [ARRAY_SIZE] = {0};

	fileOpen(&pstFile, FILE_NAME, FILE_READ_MODE);

	if(pstFile != NULL)
	{

		while(fileRead(&DeviceData, sizeof(DeviceData),
					READ_COUNT, pstFile) == SUCCESS)
		{
			if(((ucChoice == REMOVE_BY_NAME) &&
				(strcmp((char*)DeviceData.pucDeviceName,
				pucStringToCount) == STRINGS_EQUAL)) ||
				((ucChoice == REMOVE_BY_TYPE) &&
				(strcmp((char*)DeviceData.pucDeviceType,
				pucStringToCount) == STRINGS_EQUAL)) ||
				((ucChoice == REMOVE_BY_ID) &&
				(DeviceData.ulDeviceId == ulValueToCount)) ||
				((ucChoice == REMOVE_BY_VENDOR) &&
				(DeviceData.ulDeviceVendor == ulValueToCount)) ||
				((ucChoice == REMOVE_BY_SERIAL) &&
				(DeviceData.ulDeviceSerial == ulValueToCount)))
			{
				//MatchedDeviceData[ucRepeatCount++] = DeviceData;
				ucRepeatCount = ucRepeatCount + INCREMENT_BY_ONE;
				//error
				//pMatchedDeviceData->pucDeviceName = DeviceData.pucDeviceName;
				strcpy(pMatchedDeviceData->pucDeviceName, 
						DeviceData.pucDeviceName);
				strcpy(pMatchedDeviceData->pucDeviceType, 
				DeviceData.pucDeviceType);
				pMatchedDeviceData->ulDeviceId = DeviceData.ulDeviceId;
				pMatchedDeviceData->ulDeviceVendor = DeviceData.ulDeviceVendor;
				pMatchedDeviceData->ulDeviceSerial = DeviceData.ulDeviceSerial;

				pMatchedDeviceData++;
			}
		}
		fileClose(pstFile);
		printf("\n  %d Item found in data", ucRepeatCount);

		if(ucRepeatCount == 0)
		{
			printf("\n No match found");
		}		
	}
	else
	{
		printf("\n unable to open file : deviceItemRepeatCount ");
	}

	return ucRepeatCount;
}


//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To remove device data based on criteria
//Inputs	: FILE *pstFile,  pointer to the file which contains the device data
//Inputs	: uint32 ucChoice, the choice selected by user as search criteria 
//Outputs	: None
//Return	: True, at the time of successful execution
//Return	: False, in case of an error
//Notes		: None
//******************************************************************************
static bool deviceRemoveByCriteria(FILE *pstFile,
									uint32 ucChoice)
{
	bool blReturn = false;
	DEVICE_DETAILS DeviceData = {0};
	uint8 ucStringToRemove [STR_MAX_SIZE] = "";
	uint32 ulValueToRemove = 0;
	FILE *pstTemporaryFile = NULL;
	uint8 ucRemoveData = 0;
	uint8 ucKeepData = SUCCESS;
	uint8 ucRepeatCount = 0;	
	uint8 ucIteration = 0;
	uint8 ucDeletionChoice = 0;
	uint8 ucDeletionIndex = 0;
	DEVICE_DETAILS MatchedDeviceData [ARRAY_SIZE] = {0};	

	if(pstFile != NULL && 
		(ucChoice >= 0 && ucChoice <= SEARCH_CRITERIA_MAXIMUM_OPTIONS))
	{
		if(ucChoice == REMOVE_BY_NAME)
		{
			blReturn = deviceReadString("Enter Name: ",
										ucStringToRemove, STR_MAX_SIZE);
		}
		else if(ucChoice == REMOVE_BY_TYPE)
		{
			blReturn = deviceReadString("Enter Type: ",
										ucStringToRemove, STR_MAX_SIZE);
		}
		else if(ucChoice == REMOVE_BY_ID)
		{
			blReturn = deviceReadValue("Enter Id: ",
										&ulValueToRemove, READ_HEX);
		}
		else if(ucChoice == REMOVE_BY_VENDOR)
		{
			blReturn = deviceReadValue("Enter Vendor: ",
										&ulValueToRemove, READ_HEX);
		}
		else if(ucChoice == REMOVE_BY_SERIAL)
		{
			blReturn = deviceReadValue("Enter Serial: ",
										&ulValueToRemove, READ_NON_HEX);
		}
		else
		{
			printf("\nUnable to search : Invalid search criteria");
		}

		if(blReturn == SUCCESS)
		{
			ucRepeatCount = deviceItemRepeatCount(ucChoice, ulValueToRemove,
													ucStringToRemove,
													MatchedDeviceData);
			if(ucRepeatCount >= SUCCESS)
			{
				
				printf("\nMatched devices\n");
				printf("-------------------------------------------\n");

				for(ucIteration = 0; ucIteration < ucRepeatCount; ucIteration++)
				{
					printf("%hhu :\n", ucIteration + INCREMENT_BY_ONE);
					printf("Name\t\tType\t\tId\t\tVendor\t\tSerial\n");
					devicePrintData(&MatchedDeviceData[ucIteration]);
				}

				if(ucRepeatCount > SUCCESS)
				{
					printf("\n Select option for deletion\n");
					printf("-------------------------------------------\n");
					printf("1. Delete all\n");
					printf("2. Delete single\n");
					printf("0. Cancel\n");
					blReturn = scanf("%hhu",&ucDeletionChoice);
					menuFlushInput();

					if(blReturn == SUCCESS)
					{
						switch( ucDeletionChoice )
						{
							case DELETE_CANCEL:
							{
								printf("Deletion cancelled\n");
							}
							break;

							case DELETE_ALL:
							{
								printf("Delete all\n");
							}
							break;

							case DELETE_SINGLE:
							{
								printf("Delete single\n");
								printf("\nEnter index (1-%hhu) to delete : ",
										ucRepeatCount);
								scanf("%hhu",&ucDeletionIndex);
								menuFlushInput();
								//Decrement index by one
								ucDeletionIndex = 
											ucDeletionIndex - INCREMENT_BY_ONE;
								
							}
							break;

							default:
								printf("Invalid choice!\n");
						}
			
					}
				}

				if(ucDeletionChoice == DELETE_ALL ||
					ucDeletionChoice == DELETE_SINGLE || 
					ucRepeatCount == SUCCESS)
				{
					fileOpen(&pstTemporaryFile, TEMPORARY_FILE_NAME,
								FILE_WRITE_MODE);

					while(fileRead(&DeviceData, sizeof(DeviceData),
						READ_COUNT, pstFile) == SUCCESS)
					{
						//ucKeepData = SUCCESS;
						ucRemoveData = 0;

						for(ucIteration = 0; ucIteration < ucRepeatCount;
							ucIteration++)
						{
							if(memcmp(&DeviceData, 
								&MatchedDeviceData[ucIteration],
								sizeof(DeviceData)) == 0 )
							{
								if(ucDeletionChoice == DELETE_ALL)
								{
									ucRemoveData = SUCCESS;
								}
								else if(ucDeletionChoice == DELETE_SINGLE &&
										ucIteration == ucDeletionIndex)
								{
									ucRemoveData = SUCCESS;
								}
								else if(ucIteration == 0)//no repeat
								{
									ucRemoveData = SUCCESS;
								}
							}
							
						}

						if(ucRemoveData != SUCCESS)
						{
							fileWrite(&DeviceData, sizeof(DeviceData),WRITE_COUNT,
										pstTemporaryFile);
						}
					}
					fileClose(pstTemporaryFile);
					remove(FILE_NAME);
					rename(TEMPORARY_FILE_NAME,FILE_NAME);
					printf("\n Removed the item\n");

				}

				
			}
		}
	}
	else
	{
		printf("\nUnable to search by criteria : Invalid parameters");
	}

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To add a new device to the entry
//Inputs	: const uint8 *pucFileName, pointer to file to which device data is
//				updated
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: File opened in append mode
//******************************************************************************
bool deviceAdd(const uint8 *pucFileName)
{
	bool blReturn = false;
	DEVICE_DETAILS DeviceData = {0};
	FILE *pstFile = NULL;
	uint32 ulLen = 0;
	uint8 ucNameLen = 0;
	uint8 ucTypeLen = 0;

	if (pucFileName != NULL)
	{
		fileOpen(&pstFile, pucFileName, FILE_APPEND_MODE);
		
		if(pstFile != NULL)
		{
			printf("\nAdd device\n");
			printf("-----------------------------\n");
			blReturn = deviceReadData(&DeviceData, FILE_NAME);

			if(blReturn == SUCCESS)
			{
				blReturn = fileWrite(&DeviceData, sizeof(DeviceData),
									WRITE_COUNT, pstFile);
			}

			if(blReturn == SUCCESS)
			{
				printf("\n Device details updated successfully");
			}
			blReturn = fileClose(pstFile);
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
//Inputs	: const uint8 *pucFileName, name of the file name which contains the
//				device details
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: File opened in read mode
//******************************************************************************
bool deviceList(const uint8 *pucFileName)
{
	bool blReturn = false;
	DEVICE_DETAILS DeviceData = {0};
	FILE *pstFile = NULL;
	uint32 ulLen = 0;
	uint8 ucNameLen = 0;
	uint8 ucTypeLen = 0;
	
	if (pucFileName != NULL)
	{
		fileOpen(&pstFile, pucFileName, FILE_READ_MODE);

		if (pstFile != NULL)
		{
			printf("\nList device\n");
			printf("-----------------------------\n");
			printf("Name\t\tType\t\tId\t\tVendor\t\tSerial\n");
			while(fileRead(&DeviceData, sizeof(DeviceData),
					READ_COUNT, pstFile) == SUCCESS)
			{
				blReturn = devicePrintData(&DeviceData);
			}
		}
		else
		{
			printf("\nUnable to list devices : Failed to open the file");
		}
	}
	else
	{
		printf("\nUnable to list the devices : Missing file name");
	}

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To search an item in device list
//Inputs	: const uint8 *pucFileName, name of the file name which contains the
//				device details
//Inputs	: uint32 ucChoice, the choice selected by user as search criteria
//Outputs	: None
//Return	: True, at time of successful execution
//Return	: False, in case of an error
//Notes		: None
//******************************************************************************
bool deviceSearch(const uint8 *pucFileName, uint32 ucChoice)
{
	bool bReturn = false;
	FILE *pstFile = NULL;

	if(pucFileName != NULL && 
		(ucChoice >= 0 && ucChoice <= SEARCH_CRITERIA_MAXIMUM_OPTIONS))
	{
		if(ucChoice != BACK_TO_MAIN_MENU)
		{
			fileOpen(&pstFile, pucFileName, FILE_READ_MODE);
			
			if (pstFile != NULL)
			{
				deviceSearchByCriteria(pstFile, ucChoice);
				fileClose(pstFile);
				bReturn = true;
			}
			else
			{
				printf("\nUnable to search devices : Failed to open the file");
			}
			
		}
	}
	else
	{
		printf("\nUnable to search : Invalid search parameters");
	}

	return bReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To remove an item from the device list
//Inputs	: const uint8 *pucFileName, name of the file name which contains the
//				device details
//Inputs	: uint32 ucChoice, the choice selected by user as remove criteria
//Outputs	: None
//Return	: True, at time of successfull execution
//Return	: False, in case of an error
//Notes		: None
//******************************************************************************
bool deviceRemove(const uint8 *pucFileName, uint32 ucChoice)
{
	bool bReturn = false;
	FILE *pstFile = NULL;

	if(pucFileName != NULL && 
	   (ucChoice >= 0 && ucChoice <= REMOVE_CRITERIA_MAXIMUM_OPTIONS))
	{
		if(ucChoice != RETURN_TO_MAIN_MENU)
		{
			fileOpen(&pstFile, pucFileName, FILE_READ_MODE);
			
			if (pstFile != NULL)
			{
				deviceRemoveByCriteria(pstFile, ucChoice);
				fileClose(pstFile);
				bReturn = true;
			}
			else
			{
				printf("\nUnable to search devices : Failed to open the file");
			}		
			
		}
		
	}
	else
	{
		printf("\nUnable to search : Invalid search parameters");
	}

	return bReturn;
}
// EOF