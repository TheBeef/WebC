/*******************************************************************************
 * FILENAME: FileServer.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    Other example
 *
 * COPYRIGHT:
 *    Copyright (c) 2019 Paul Hutchinson
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
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "BittyHTTP/WebServer.h"
#include "Pages.h"
#include "main.h"
#include "Pages.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

struct OtherInfo
{
    const char *Filename;   // With Path
    void (*WriteFile)(void);
};

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/
struct OtherInfo m_Other[]=
{
    {"/css/MainCSS.css",Page_MainCSS},
    {"/graphics/sport_soccer.png",Page_sport_soccer},
};

struct WebServer *g_Web;

/*******************************************************************************
 * NAME:
 *    FS_GetFileProperties
 *
 * SYNOPSIS:
 *    bool FS_GetFileProperties(const char *Filename,
 *          struct WSPageProp *PageProp);
 *
 * PARAMETERS:
 *    Filename [I] -- The filename from the URL that is being requested.
 *    PageProp [O] -- This is filled in with info about the page.
 *                      FileID -- The ID of the page.  This has no meaning
 *                                to the web server it is just passed back
 *                                to FS_SendFile().  It can hold a pointer.
 *                      DynamicFile -- If this is true then the file will
 *                                     no be cached.  false will set the
 *                                     ETAG to 'DOCVER' where it will not
 *                                     resent to the browser until 'DOCVER'
 *                                     changes.
 *                      Cookies -- A pointer to the list of cookies that this
 *                                 page accepts.
 *                      Gets -- A pointer to the list of GET vars that this
 *                              page accepts.
 *                      Posts -- A pointer to the list of POST vars that this
 *                               page accepts.
 *
 * FUNCTION:
 *    This function is called when a new request comes in for a file.  This
 *    is before the headers for this request have been processed and the
 *    web server is not yet ready to send a reply.
 *
 *    The web server does need to know if this is a valid file and some info
 *    about the file.  That is what this function provides.
 *
 * RETURNS:
 *    true -- File known and can be sent
 *    false -- File is known.  Will produce a 404 reply.
 *
 * SEE ALSO:
 *    FS_SendFile()
 ******************************************************************************/
bool FS_GetFileProperties(const char *Filename,struct WSPageProp *PageProp)
{
    int r;

//    for(r=0;r<sizeof(m_Files)/sizeof(struct FileInfo);r++)
//    {
//        if(strcmp(Filename,m_Files[r].Filename)==0)
//        {
//            PageProp->FileID=(uintptr_t)&m_Files[r];
//            PageProp->DynamicFile=m_Files[r].Dynamic;
//            PageProp->Cookies=m_Files[r].Cookies;
//            PageProp->Gets=m_Files[r].Gets;
//            PageProp->Posts=m_Files[r].Posts;
//            return true;
//        }
//    }

    /* Check for graphics first */
    for(r=0;r<sizeof(m_Other)/sizeof(struct OtherInfo);r++)
    {
        if(strcmp(Filename,m_Other[r].Filename)==0)
        {
            PageProp->FileID=1000+r;
            PageProp->DynamicFile=false;
            PageProp->Cookies=NULL;
            PageProp->Gets=NULL;
            PageProp->Posts=NULL;
            return true;
        }
    }

    /* Check for wc pages */
    for(r=0;r<e_PageMAX;r++)
    {
        if(strcmp(Filename,g_Pages[r].URL)==0)
        {
            PageProp->FileID=r;
            PageProp->DynamicFile=true;
            PageProp->Cookies=g_Pages[r].Cookies;
            PageProp->Gets=g_Pages[r].Gets;
            PageProp->Posts=g_Pages[r].Posts;
            return true;
        }
    }

    return false;
}

/*******************************************************************************
 * NAME:
 *    FS_SendFile
 *
 * SYNOPSIS:
 *    void FS_SendFile(struct WebServer *Web,uintptr_t FileID);
 *
 * PARAMETERS:
 *    Web [I] -- The web context for this web connection.
 *    FileID [I] -- The number that was setup in FS_GetFileProperties().
 *                  This has no meaning to the web server and is just passed
 *                  to this function.  It can be a pointer to some object
 *                  of your defining.
 *
 * FUNCTION:
 *    This function is called from the web server when it is time to send the
 *    contents of a "file".  You may also set headers using WS_Header() as
 *    long as you haven't sent anything else yet.
 *
 * RETURNS:
 *    NONE
 *
 * SEE ALSO:
 *    WS_Header(), WS_WriteWhole(), WS_WriteChunk(), WS_GET(), WS_COOKIE(),
 *    WS_POST(), WS_SetCookie()
 ******************************************************************************/
void FS_SendFile(struct WebServer *Web,uintptr_t FileID)
{
    int Index;

    g_Web=Web;

    if(FileID>=1000)
    {
        /* Other files */
        Index=FileID-1000;
        m_Other[Index].WriteFile();
    }
    else
    {
        /* Page ID */
        g_PageID=FileID;

        g_Pages[g_PageID].PageFn();
    }
}
