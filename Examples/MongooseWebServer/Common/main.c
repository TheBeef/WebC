/*******************************************************************************
 * FILENAME: main.c
 *
 * PROJECT:
 *    WebC
 *
 * FILE DESCRIPTION:
 *    This file is the main entry for the examples.  It brings up the Mongoose
 *    web server and serves the example files.
 *
 * COPYRIGHT:
 *    Copyright (c) 2026 Paul Hutchinson
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
#include "mongoose.h"   // To build, run: cc main.c mongoose.c
#include "FileServer.h"

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

// HTTP server event handler function
void ev_handler(struct mg_connection *c, int ev, void *ev_data)
{
    if (ev == MG_EV_HTTP_MSG)
    {
        ServePages(c,ev,ev_data);
    }
}

int main(void)
{
    struct mg_mgr mgr;  // Declare event manager

    printf("Waiting for connections on port 8080 (http://localhost:8080)\n");

    mg_mgr_init(&mgr);  // Initialise event manager
    mg_http_listen(&mgr,"http://0.0.0.0:8080",ev_handler,NULL);  // Setup listener

    for(;;)
    {          // Run an infinite event loop
        mg_mgr_poll(&mgr, 1000);
    }
    return 0;
}
