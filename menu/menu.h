//************************** DEVICE MANAGEMENT SYSTEM **************************
//  Copyright (c) 2025 Trenser Technology Solutions
//  All Rights Reserved
//******************************************************************************
//
// Summary	: To manage a menu in a device management system
// Note		: Handle different menus for device management system
//
//******************************************************************************

#ifndef MENU_H
#define MENU_H

//******************************* Include Files ********************************
#include <stdbool.h>
#include "customTypes.h"

//******************************* Global Types *********************************

//***************************** Global Constants *******************************

//***************************** Global Variables *******************************
typedef enum{
	MENU_EXIT,
	MENU_ADD,
	MENU_LIST,
	MENU_SEARCH,
	MENU_REMOVE
}MENU_OPTIONS;

//**************************** Forward Declarations ****************************
bool menuMain(void);

#endif // MENU_H
// EOF