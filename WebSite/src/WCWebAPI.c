/*******************************************************************************
 * FILENAME: WCWebAPI.c
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
 *    Paul Hutchinson (29 Oct 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "FileServer.h"
#include "WCWebAPI.h"
#include <stdio.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

void wcecho(const char *buff)
{
    WS_WriteChunkStr(g_Web,buff);
}

void wcwrite(const unsigned char *bin,int Len)
{
    WS_WriteWhole(g_Web,(const char *)bin,Len);
}

void wcSetMine(const char *Mime)
{
    char buff[256];
    sprintf(buff,"Content-Type: %s",Mime);
    WS_Header(g_Web,buff);
}

