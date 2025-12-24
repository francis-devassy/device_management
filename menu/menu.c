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
#include "customTypes.h"
#include "menu.h"
#include "device.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: Display the contents in main menu 
//Inputs	: None
//Outputs	: None
//Return	: Return the option selected
//Notes		: The selected option is used to move to the next level
//******************************************************************************
static uint8 menuDisplay(void)
{
	uint8 ucChoice = 0;

	printf("\nMenu\n");
	printf("-----------------------------\n");
	printf("1. Add device\n");
	printf("2. List devices\n");
	printf("3. Search device\n");
	printf("4. Remove device\n");
	printf("0. Exit\n");
	printf("Enter choice: ");
	scanf("%hhu", &ucChoice);
	return ucChoice;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: Navigte from main menu to next levels based on the 
//			  selected options
//Inputs	: None
//Outputs	: None
//Return	: True, in case of successful execution
//Return	: False, in case of any error
//Notes		: Select exit option to terminate
//******************************************************************************
bool menuMain(void)
{
	bool blReturn = false;
	uint8 ucChoice = 0;
	uint8 ucId = 0;

	printf("Device Management System\n\n");

	do 
	{
		ucChoice = menuDisplay();
		//printf("\n Selected  choice is  %hhu \n", ucChoice);

		switch( ucChoice )
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
				printf("Enter device ID to search: ");
				scanf("%hhd", &ucId);
				deviceSearch(FILE_NAME, ucId);
			}
			break;

			case MENU_REMOVE:
			{
				printf("Enter device ID to remove: ");
				scanf("%hhd", &ucId);
				deviceRemove(FILE_NAME, ucId);
			}
			break;

			default:
				printf("Invalid choice!\n");
		}
	}
	while (ucChoice != 0);

	return blReturn;
}
// EOF
