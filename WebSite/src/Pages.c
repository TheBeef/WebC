/*******************************************************************************
 * FILENAME: Pages.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
 *
 * CREATED BY:
 *    Paul Hutchinson (31 Oct 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "Pages.h"
#include "WCWebAPI.h"
#include <stdlib.h>
#include <stdio.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/
e_PageType g_PageID;

struct PageInfo g_Pages[e_PageMAX]=
{
    {"/","Main Index",                  e_PageMAX,          NULL,NULL,NULL,Page_Index},
    {"/Links.wc","Links",               e_PageMAX,          NULL,NULL,NULL,Page_Links},
    {"/About.wc","About WebC",          e_PageMAX,          NULL,NULL,NULL,Page_About},
    {"/Contact.wc","Contact",           e_PageMAX,          NULL,NULL,NULL,Page_Contact},
    {"/Downloads.wc","Downloads",       e_PageMAX,          NULL,NULL,NULL,Page_Downloads},
    {"/Examples.wc","Examples",         e_PageMAX,          NULL,NULL,NULL,Page_Examples},
    {"/Ex1.wc","Hello World Example",   e_Page_Examples,    NULL,NULL,NULL,Page_Ex1},
    {"/Ex2.wc","Globals Example",       e_Page_Examples,    NULL,NULL,NULL,Page_Ex2},
    {"/Ex3.wc","Graphic files",         e_Page_Examples,    NULL,NULL,NULL,Page_Ex3},
    {"/Ex4.wc","Short Echo Tag",        e_Page_Examples,    NULL,NULL,NULL,Page_Ex4},
    {"/Ex5.wc","Strings",               e_Page_Examples,    NULL,NULL,NULL,Page_Ex5},
    {"/Ex6.wc","Page Functions",        e_Page_Examples,    NULL,NULL,NULL,Page_Ex6},
    {"/Ex7.wc","Short Tag",             e_Page_Examples,    NULL,NULL,NULL,Page_Ex7},
    {"/ExMakefile.wc","Makefile",       e_Page_Examples,    NULL,NULL,NULL,Page_ExMakefile},
};

void OutputLink(e_PageType PageID,const char *LinkTxt)
{
    wcecho("<a href='");
    wcecho(g_Pages[PageID].URL);
    wcecho("'>");
    wcecho(LinkTxt);
    wcecho("</a>");
}

void BuildLink(e_PageType PageID,const char *LinkTxt,char *outbuff,int MaxSize)
{
    snprintf(outbuff,MaxSize,"<a href='%s'>%s</a>",g_Pages[PageID].URL,
            LinkTxt);
}
