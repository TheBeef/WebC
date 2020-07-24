/*******************************************************************************
 * FILENAME: Utils.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
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
