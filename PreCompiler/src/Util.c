/*******************************************************************************
 * FILENAME: Util.c
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
 *    Paul Hutchinson (28 Oct 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "Util.h"
#include <string.h>
#include <stdio.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

int GetFnNameFromFilename(struct SourceFile *SFile,char *FnName,int MaxFnName)
{
    char *e;
    char *s;

    /* Build a page function name for this file */
    if(SFile->FilenameExt!=NULL)
        e=SFile->FilenameExt-1;
    else
        e=&SFile->Filename[strlen(SFile->Filename)];
    /* Search from the end to find the start of the filename */
    s=e-1;
    while(s>=SFile->Filename)
    {
        if((*s>='a' && *s<='z') || (*s>='A' && *s<='Z') || (*s>='0' && *s<='9')
                || *s=='_')
        {
            /* Valid char */
            s--;
        }
        else
        {
            /* End of the filename (and or acceptable chars) */
            if(*s!='/' && *s!='\\' && *s!=':')
            {
                fprintf(stderr,"error: Filename %s contains char's that are "
                        "not part of a valid C function name "
                        "(%c is invalid).\n",SFile->Filename,*s);
                return 1;
            }
            break;
        }
    }
    /* Copy the filename */
    if(e-s-1>MaxFnName)
    {
        fprintf(stderr,"error: Internal buffer overflow making page "
                "function name.  Filename can only be %d bytes in length\n",
                MaxFnName);
        return 1;
    }
    strcpy(FnName,"Page_");
    FnName[strlen(FnName)+e-s-1]=0;
    memcpy(&FnName[strlen(FnName)],s+1,e-s-1);

    return 0;
}
