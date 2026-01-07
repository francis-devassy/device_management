//************************** DEVICE MANAGEMENT SYSTEM **************************
//  Copyright (c) 2025 Trenser Technology Solutions
//  All Rights Reserved
//******************************************************************************
//
// Summary	: Handle options related to file handling
// Note		: Feature to open, close and write to file
//
//******************************************************************************

#ifndef _FILE_H_
#define _FILE_H_

//******************************* Include Files ********************************
#include <stdio.h>
#include <stdbool.h>
#include "customTypes.h"

//******************************* Global Types *********************************

//***************************** Global Constants *******************************
#define FILE_READ_MODE		"rb"
#define FILE_APPEND_MODE	"ab"
#define FILE_WRITE_MODE		"wb"
//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
bool fileOpen(FILE **ppstFile, const uint8 *pucFileName, const uint8 *pucMode);
bool fileClose(FILE *pstFile);
bool fileWrite(const void *pData, uint32 ulDataSize, uint32 ulDataCount,
				FILE *pstFile);
bool fileRead(void *pData, uint32 ulDataSize, uint32 ulDataCount,
				FILE *pstFile);

#endif // _FILE_H_
// EOF