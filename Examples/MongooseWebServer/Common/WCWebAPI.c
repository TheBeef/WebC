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
 *    Copyright 10 Jun 2026 Paul Hutchinson.
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *    
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 *
 * CREATED BY:
 *    Paul Hutchinson (10 Jun 2026)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "WCWebAPI.h"
#include "FileServer.h"

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

void wcecho(const char *buff)
{
    if(!g_HeaderSent)
    {
        mg_printf(g_Web,
                "HTTP/1.1 200 OK\r\n"
                "Transfer-Encoding: chunked\r\n"
                "\r\n");
        g_HeaderSent=true;
        g_DoingChunks=true;
    }

    mg_http_printf_chunk(g_Web,"%s",buff);
}

void wcwrite(const unsigned char *bin,int Len)
{
    mg_printf(g_Web,"Content-Length: %d\r\n",Len);
    mg_printf(g_Web,"\r\n");
    mg_send(g_Web,bin,Len);
}

void wcSetMine(const char *Mime)
{
    if(!g_HeaderSent)
    {
        mg_printf(g_Web,
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: %s\r\n",Mime);
        g_HeaderSent=true;
        g_DoingChunks=false;
    }
}

