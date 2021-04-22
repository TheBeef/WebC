/*******************************************************************************
 * FILENAME: Pages.h
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
 * HISTORY:
 *    Paul Hutchinson (28 Oct 2019)
 *       Created
 *
 *******************************************************************************/
#ifndef __PAGES_H_
#define __PAGES_H_

/***  HEADER FILES TO INCLUDE          ***/

/***  DEFINES                          ***/

/***  MACROS                           ***/

/***  TYPE DEFINITIONS                 ***/
typedef enum
{
    e_Page_Index,
    e_Page_Links,
    e_Page_About,
    e_Page_Contact,
    e_Page_Downloads,
    e_Page_Documentation,
    e_Page_License,
    e_Page_Examples,
    e_Page_Ex1,
    e_Page_Ex2,
    e_Page_Ex3,
    e_Page_Ex4,
    e_Page_Ex5,
    e_Page_Ex6,
    e_Page_Ex7,
    e_Page_ExMakefile,
    e_Page_ReleaseNotes,
    e_PageMAX
} e_PageType;

struct PageInfo
{
    const char *URL;
    const char *Title;
    e_PageType Parent;
    const char **Cookies;
    const char **Gets;
    const char **Posts;
    void (*PageFn)(void);
};

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/
extern struct PageInfo g_Pages[e_PageMAX];
extern e_PageType g_PageID;

/***  EXTERNAL FUNCTION PROTOTYPES     ***/
void OutputLink(e_PageType PageID,const char *LinkTxt);
void OutputLinkWithAnchor(e_PageType PageID,const char *Anchor,const char *LinkTxt);
void BuildLink(e_PageType PageID,const char *LinkTxt,char *outbuff,int MaxSize);

void Page_Index(void);
void Page_Links(void);
void Page_About(void);
void Page_Contact(void);
void Page_Downloads(void);
void Page_Documentation(void);
void Page_License(void);
void Page_Examples(void);
void Page_Ex1(void);
void Page_Ex2(void);
void Page_Ex3(void);
void Page_Ex4(void);
void Page_Ex5(void);
void Page_Ex6(void);
void Page_Ex7(void);
void Page_ExMakefile(void);
void Page_DisplayReleaseNotes(void);

void Page_MainCSS(void);
void Page_sport_soccer(void);

void Page_LinuxWebCC(void);
void Page_WindowsWebCC(void);
void Page_makefile(void);
void Page_SourceWebCC(void);
void Page_ExampleDownload(void);
void Page_WebSiteDownload(void);

#endif
