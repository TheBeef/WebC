/*******************************************************************************
 * FILENAME: WCWebAPI.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
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

