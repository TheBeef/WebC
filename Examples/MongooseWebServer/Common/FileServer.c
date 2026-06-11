/*******************************************************************************
 * FILENAME: FileServer.c
 *
 * PROJECT:
 *    WebC
 *
 * FILE DESCRIPTION:
 *    File server for WebC examples
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
#include "mongoose.h"
#include "FileServer.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/
struct FileInfo
{
    const char *Filename;   // With Path
    void (*PageFn)(void);
};

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/
struct mg_connection *g_Web;
bool g_HeaderSent;
bool g_DoingChunks;

#include "ExampleFiles.h"

void ServePages(struct mg_connection *c, int ev, void *ev_data)
{
    unsigned int r;
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;  // Parsed HTTP request

    g_Web=c;

    g_HeaderSent=false;
    g_DoingChunks=false;

    for(r=0;r<sizeof(m_Files)/sizeof(struct FileInfo);r++)
    {
        if(mg_match(hm->uri,mg_str(m_Files[r].Filename),NULL))
        {
            m_Files[r].PageFn();
            
            mg_http_printf_chunk(g_Web,"");    // Done
            break;
        }
    }
    if(r==sizeof(m_Files)/sizeof(struct FileInfo))
    {
        /* Not found */
        mg_http_reply(c, 404,
                "Content-Type: text/html\r\n",
                "<h1>404 Error</h1>"
                "<p>The requested page was not found.</p>\n");
    }
}

