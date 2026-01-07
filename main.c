//************************** DEVICE MANAGEMENT SYSTEM **************************
//  Copyright (c) 2025 Trenser Technology Solutions
//  All Rights Reserved
//******************************************************************************
//
// File		: main.c
// Summary	: Device management system to add, list, search and remove items to 
//			  the data history
// Note		: A menu driven system to manage devices data history
// Author	: Francis V D
// Date		: 22-December-2025
//
//******************************************************************************

//******************************* Include Files ********************************
#include <stdio.h>
#include "menu.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.FUNCTION_HEADER.*******************************
//Purpose	: Calls the main menu to start the menu driven system 
//Inputs	: None
//Outputs	: None
//Return	: Return 0 at time of successful execution
//Return	: Returns a non-zero integer value in case of an error
//Notes		: Code execution begins from here 
//******************************************************************************
int main()
{
	menuMain();
	
	return 0;
}
// EOF