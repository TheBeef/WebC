/*******************************************************************************
 * FILENAME: Pages.c
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
    {"/","WebC",                            e_PageMAX,          NULL,NULL,NULL,Page_Index},
    {"/Links.wc","Links",                   e_PageMAX,          NULL,NULL,NULL,Page_Links},
    {"/About.wc","About WebC",              e_PageMAX,          NULL,NULL,NULL,Page_About},
    {"/Contact.wc","Contact",               e_PageMAX,          NULL,NULL,NULL,Page_Contact},
    {"/Downloads.wc","Downloads",           e_PageMAX,          NULL,NULL,NULL,Page_Downloads},
    {"/Documentation.wc","Documentation",   e_PageMAX,          NULL,NULL,NULL,Page_Documentation},
    {"/License.wc","License",               e_PageMAX,          NULL,NULL,NULL,Page_License},
    {"/Examples.wc","Examples",             e_PageMAX,          NULL,NULL,NULL,Page_Examples},
    {"/Ex1.wc","Hello World Example",       e_Page_Examples,    NULL,NULL,NULL,Page_Ex1},
    {"/Ex2.wc","Globals Example",           e_Page_Examples,    NULL,NULL,NULL,Page_Ex2},
    {"/Ex3.wc","Graphic files",             e_Page_Examples,    NULL,NULL,NULL,Page_Ex3},
    {"/Ex4.wc","Short Echo Tag",            e_Page_Examples,    NULL,NULL,NULL,Page_Ex4},
    {"/Ex5.wc","Strings",                   e_Page_Examples,    NULL,NULL,NULL,Page_Ex5},
    {"/Ex6.wc","Page Functions",            e_Page_Examples,    NULL,NULL,NULL,Page_Ex6},
    {"/Ex7.wc","Short Tag",                 e_Page_Examples,    NULL,NULL,NULL,Page_Ex7},
    {"/ExMakefile.wc","Makefile",           e_Page_Examples,    NULL,NULL,NULL,Page_ExMakefile},
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
