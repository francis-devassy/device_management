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
#define MENU_MAIN_OPTIONS_MAX			(4)
#define MENU_SECONDARY_OPTIONS_MAX		(5)
#define SEARCH_CRITERIA_MAXIMUM_OPTIONS	(5)
#define REMOVE_CRITERIA_MAXIMUM_OPTIONS	(5)
#define MENU_DELETE_OPTIONS_MAX			(2)

//***************************** Global Variables *******************************
typedef enum{
	MENU_EXIT,
	MENU_ADD,
	MENU_LIST,
	MENU_SEARCH,
	MENU_REMOVE
}MENU_OPTIONS;

typedef enum{
	BACK_TO_MAIN_MENU,
	SEARCH_BY_NAME,
	SEARCH_BY_TYPE,
	SEARCH_BY_ID,
	SEARCH_BY_VENDOR,
	SEARCH_BY_SERIAL
}SEARCH_OPTIONS;

typedef enum{
	RETURN_TO_MAIN_MENU,
	REMOVE_BY_NAME,
	REMOVE_BY_TYPE,
	REMOVE_BY_ID,
	REMOVE_BY_VENDOR,
	REMOVE_BY_SERIAL
}REMOVE_OPTIONS;

typedef enum{
	DELETE_CANCEL,
	DELETE_ALL,
	DELETE_SINGLE
}DELETE_OPTIONS;

//**************************** Forward Declarations ****************************
bool menuMain(void);
bool menuFlushInput(void);
uint8 menuDisplayDeleteOptions(void);

#endif // MENU_H
// EOF