/*******************************************************************************
 * FILENAME: Utils.c
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
 *    Paul Hutchinson (01 Nov 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "Utils.h"
#include "WCWebAPI.h"
#include <stdbool.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/
static void In_OutputHTMLExampleCode(const char *HTML,bool IncludeWebCTags);

/*** VARIABLE DEFINITIONS     ***/

void OutputHTMLExampleCode(const char *HTML)
{
    In_OutputHTMLExampleCode(HTML,true);
}

void OutputHTMLExampleCodeNoWC(const char *HTML)
{
    In_OutputHTMLExampleCode(HTML,false);
}

static void In_OutputHTMLExampleCode(const char *HTML,bool IncludeWebCTags)
{
    char buff[100];
    char *d;
    const char *s;

    s=HTML;
    d=buff;
    while(*s!=0)
    {
        if(*s=='<')
        {
            *d++='&';
            *d++='l';
            *d++='t';
            *d++=';';
        }
        else if(*s=='>')
        {
            *d++='&';
            *d++='g';
            *d++='t';
            *d++=';';
        }
        else if(*s=='&')
        {
            *d++='&';
            *d++='a';
            *d++='m';
            *d++='p';
            *d++=';';
        }
        else if(IncludeWebCTags && *s=='`')
        {
            *d++='&';
            *d++='l';
            *d++='t';
            *d++=';';
            *d++='?';
        }
        else if(IncludeWebCTags && *s=='$')
        {
            *d++='?';
            *d++='&';
            *d++='g';
            *d++='t';
            *d++=';';
        }
        else
        {
            *d++=*s;
        }

        if(d-buff>sizeof(buff)-7)
        {
            /* Ok, we are past the point we need to insert the next char,
               string it and output it */
            *d=0;
            wcecho(buff);
            d=buff;
        }

        s++;
    }
    if(d!=buff)
    {
        *d=0;
        wcecho(buff);
    }
}
