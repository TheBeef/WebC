/*******************************************************************************
 * FILENAME: ProcessFile.c
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
 * CREATED BY:
 *    Paul Hutchinson (24 Oct 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "ProcessFile.h"
#include "ProcessWebC.h"
#include "ProcessBin.h"
#include "Options.h"
#include <stdio.h>
#include <string.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/
int Process(struct SourceFile *SFile)
{
    char OutFileName[256];
    int ExtSize;

    ExtSize=strlen(g_Options.OutputExt);

    if(strlen(SFile->Filename)>sizeof(OutFileName)-ExtSize)
    {
        fprintf(stderr,"error: filename to long (%s)\n",SFile->Filename);
        return 1;
    }

    if(g_Options.OutputFilename[0]!=0)
    {
        strcpy(OutFileName,g_Options.OutputFilename);
    }
    else
    {
        strcpy(OutFileName,SFile->Filename);
        if(SFile->FilenameExt!=NULL)
            OutFileName[SFile->FilenameExt-SFile->Filename-1]=0;
        strcat(OutFileName,g_Options.OutputExt);
    }

    switch(SFile->FileType)
    {
        case e_SourceFile_WC:
            return ProcessWebCFile(SFile,OutFileName);
        break;
        case e_SourceFile_C:
        case e_SourceFile_H:
            /* We don't do any processing on these */
        break;
        case e_SourceFile_Binary:
            return ProcessBinFile(SFile,OutFileName);
        break;
        case e_SourceFileMAX:
        break;
    }
    return 0;
}
