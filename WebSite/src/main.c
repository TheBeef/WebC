/*******************************************************************************
 * FILENAME: main.c
 *
 * PROJECT:
 *    WebC
 *
 * FILE DESCRIPTION:
 *    This is an example main loop.
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
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "main.h"
#include "BittyHTTP/WebServer.h"
#include <stdint.h>
#include <stdio.h>

#include <unistd.h> // usleep()

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/
bool g_Quit;

int main(void)
{
    t_ElapsedTime Waiting2End;

    SocketsCon_InitSocketConSystem();
    WS_Init();

    if(!WS_Start(3000))
    {
        printf("Failed to start web server\n");
        return 0;
    }

    printf("Waiting for connections on port 3000\n");

    g_Quit=false;
    while(!g_Quit)
    {
        WS_Tick();
        usleep(1000);
    }

    printf("Quiting...\n");

    /* Run the web server for a while so we can send any "finished" page */
    Waiting2End=ReadElapsedClock();
    while(ReadElapsedClock()-Waiting2End<3)
        WS_Tick();

    WS_Shutdown();
    SocketsCon_ShutdownSocketConSystem();

    return 0;
}

/*******************************************************************************
 * NAME:
 *    ReadElapsedClock
 *
 * SYNOPSIS:
 *    t_ElapsedTime ReadElapsedClock(void);
 *
 * PARAMETERS:
 *    NONE
 *
 * FUNCTION:
 *    This function reads a system clock (in seconds) and can be used for
 *    for elapsed time readings (basicly timers where you store the start
 *    time and then subtract the current value and see if it bigger than
 *    your timeout).
 *
 *    There is no need for this to be a real time clock, just something that
 *    counts up.
 *
 * RETURNS:
 *    The current clock time in seconds.
 *
 * SEE ALSO:
 *    
 ******************************************************************************/
t_ElapsedTime ReadElapsedClock(void)
{
    time_t Current; // The current time

    Current=time(NULL);

    return (uint32_t)Current;
}
