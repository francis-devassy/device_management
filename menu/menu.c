//************************** DEVICE MANAGEMENT SYSTEM **************************
//  Copyright (c) 2025 Trenser Technology Solutions
//  All Rights Reserved
//******************************************************************************
//
// File		: menu.c
// Summary	: List initial menu for a menu driven system
// Note		: The next level progression based on decisions from initial menu
// Author	: Francis V D
// Date		: 22-December-2025
//
//******************************************************************************

//******************************* Include Files ********************************
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "customTypes.h"
#include "menu.h"
#include "device.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: Validate the choice selected from menu option 
//Inputs	: uint8 ucChoice, the choice which is to be validated
//				uint8 ucLimit, the maximum limit for the choice
//Outputs	: None
//Return	: True, if the choice is valid
//Return	: False, if the choice is invalid
//Notes		: None
//******************************************************************************
static bool menuValidateChoice(uint8 ucChoice, uint8 ucMaximumLimit)
{
	bool blReturn = false;

	if((ucChoice < 0) || (ucChoice > ucMaximumLimit))
	{
		printf("\nInavlid input: Input validation failed\n");
	}
	else
	{
		blReturn = true;
	}

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: Display the contents in secondary menu 
//Inputs	: None
//Outputs	: None
//Return	: Return the option selected
//Notes		: The selected option is used to move to the next level
//******************************************************************************
static uint8 menuDisplaySeconadryOptions(void)
{
	uint8 ucChoice = 0;
	bool blResult = false;

	do
	{
		printf("1. Name\n");
		printf("2. Type\n");
		printf("3. Id\n");
		printf("4. Vendor\n");
		printf("5. Serial\n");
		printf("0. Back to main menu\n");
		printf("Enter choice: ");
		blResult = scanf("%hhu", &ucChoice);
		menuFlushInput();

		if(blResult == SUCCESS)
		{
			blResult = menuValidateChoice(ucChoice,MENU_SECONDARY_OPTIONS_MAX);
		}
		else
		{
			printf("\nInavlid input: Input read failed");
		}

	}
	while (blResult != SUCCESS);

	return ucChoice;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: Display the contents in main menu
//Inputs	: None
//Outputs	: None
//Return	: Return the option selected
//Notes		: The selected option is used to move to the next level
//******************************************************************************
static uint8 menuDisplayMainOptions(void)
{
	uint8 ucChoice = 0;
	bool blResult = false;

	do
	{
		printf("\nMenu\n");
		printf("-----------------------------\n");
		printf("1. Add device\n");
		printf("2. List devices\n");
		printf("3. Search device\n");
		printf("4. Remove device\n");
		printf("0. Exit\n");
		printf("Enter choice: ");
		blResult = scanf("%hhu", &ucChoice);
		menuFlushInput();

		if(blResult == SUCCESS)
		{
			blResult = menuValidateChoice(ucChoice, MENU_MAIN_OPTIONS_MAX);
		}
		else
		{
			printf("\nInavlid input: Input read failed\n");
		}
	}
	while (blResult != SUCCESS);

	return ucChoice;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: To clear the buffer after each user input read
//Inputs	: None
//Outputs	: None
//Return	: True, in case of successful execution
//Return	: False, in case of any error
//Notes		: None
//******************************************************************************
bool menuFlushInput(void)
{
	bool blReturn = false;
	uint8 ucInput;

	while ((ucInput = getchar()) != '\n' && ucInput != EOF)
	{
		//NOP
	}
	blReturn = true;

	return blReturn;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: Navigte from main menu to next levels based on the 
//				selected options
//Inputs	: None
//Outputs	: None
//Return	: True, in case of successful execution
//Return	: False, in case of any error
//Notes		: Select exit option to terminate
//******************************************************************************
bool menuMain(void)
{
	bool blReturn = false;
	uint8 ucMainChoice = 0;
	uint8 ucSecondaryChoice = 0;

	printf("Device Management System");

	do 
	{
		ucMainChoice = menuDisplayMainOptions();
		
		switch( ucMainChoice )
		{
			case MENU_EXIT:
			{
				printf("Exiting...\n");
			}
			break;

			case MENU_ADD:
			{
				deviceAdd(FILE_NAME);
			}
			break;

			case MENU_LIST:
			{
				deviceList(FILE_NAME); 
			}
			break;

			case MENU_SEARCH:
			{
				printf("\nSearch device\n");
				printf("-----------------------------\n");
				printf("Select the search criteria:\n");
				ucSecondaryChoice = menuDisplaySeconadryOptions();
				deviceSearch(FILE_NAME, ucSecondaryChoice);
			}
			break;

			case MENU_REMOVE:
			{
				printf("\nRemove device\n");
				printf("-----------------------------\n");
				printf("Select the removal criteria:\n");
				ucSecondaryChoice = menuDisplaySeconadryOptions();				
				deviceRemove(FILE_NAME, ucSecondaryChoice);
			}
			break;

			default:
				printf("Invalid choice!\n");
		}
	}
	while (ucMainChoice != 0);

	return blReturn;
}
// EOF
