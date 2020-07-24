/*******************************************************************************
 * FILENAME: Options.h
 * 
 * PROJECT:
 *    WebC
 *
 * FILE DESCRIPTION:
 *    
 *
 * COPYRIGHT:
 *    Copyright (C) 2019  Paul Hutchinson
 *
 *    This file is part of WebC.
 *
 *    This WebC is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * HISTORY:
 *    Paul Hutchinson (23 Oct 2019)
 *       Created
 *
 *******************************************************************************/
#ifndef __OPTIONS_H_
#define __OPTIONS_H_

/***  HEADER FILES TO INCLUDE          ***/
#include "SourceFiles.h"
#include <stdbool.h>

/***  DEFINES                          ***/

/***  MACROS                           ***/

/***  TYPE DEFINITIONS                 ***/
struct Options
{
    char OutputFilename[256];
    char OutputExt[256];            // The extention we take on to our output
    e_SourceFileType ForceFileType; // What file to force the input to be processed as
    char ForcedMIMEType[256];       // If we are forcing the mime type for bin files this will be it
};

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/
extern struct Options g_Options;

/***  EXTERNAL FUNCTION PROTOTYPES     ***/

#endif
