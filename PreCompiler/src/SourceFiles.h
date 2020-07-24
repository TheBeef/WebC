/*******************************************************************************
 * FILENAME: SourceFiles.h
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
#ifndef __SOURCEFILES_H_
#define __SOURCEFILES_H_

/***  HEADER FILES TO INCLUDE          ***/
#include <stdbool.h>

/***  DEFINES                          ***/

/***  MACROS                           ***/

/***  TYPE DEFINITIONS                 ***/
typedef enum
{
    e_SourceFile_WC,
    e_SourceFile_C,
    e_SourceFile_H,
    e_SourceFile_Binary,
    e_SourceFileMAX
} e_SourceFileType;

struct SourceFile
{
    char *Filename;
    char *FilenameExt;
    e_SourceFileType FileType;
    struct SourceFile *Next;
};

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/
extern struct SourceFile *g_FirstSourceFile;

/***  EXTERNAL FUNCTION PROTOTYPES     ***/
bool AddNewSourceFile(const char *Filename,e_SourceFileType FileType);
int GetSourceFileCount(void);
void ShowList(void);

#endif
