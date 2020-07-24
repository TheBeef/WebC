/* TODO:
    * Web Engine(s)
        x stdio
        x BittyHTTP
        * CGI
    * Binary to C
    * Write Supporting files (main.c, pages.c)
    * Standard functions????
        * wcecho()
        * wcwrite()
        * wcSetMime()
        GET[]?
        POST[]?
        COOKIE[]?
        HEADERS[]?

Block Rules:
    * System starts in HTML mode
    * <? ?> at top is global space
    * any HTML goes into page function unless the C scope is > 0
*/

/*******************************************************************************
 * FILENAME: main.c
 *
 * PROJECT:
 *    WebC
 *
 * FILE DESCRIPTION:
 *    
 *
 * COPYRIGHT:
 *    Copyright (C) 2020  Paul Hutchinson
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
 *
 * CREATED BY:
 *    Paul Hutchinson (24 Jul 2020)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include <stdio.h>
#include "CmdLine.h"
#include "TimeStamp.h"
#include "Options.h"
#include "SourceFiles.h"
#include "ProcessFile.h"

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

int main(int argv,char **argc)
{
    int RetValue;
    struct SourceFile *Cur;

    RetValue=ProcessArgs(argv,argc);
    if(RetValue>0)
        return RetValue;

    for(Cur=g_FirstSourceFile;Cur!=NULL;Cur=Cur->Next)
    {
//        printf("Processing %s\n",Cur->Filename);
        Process(Cur);
    }

    return 0;
}
