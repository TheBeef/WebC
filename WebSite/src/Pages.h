/*******************************************************************************
 * FILENAME: Pages.h
 * 
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
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
    e_Page_Examples,
    e_Page_Ex1,
    e_Page_Ex2,
    e_Page_Ex3,
    e_Page_Ex4,
    e_Page_Ex5,
    e_Page_Ex6,
    e_Page_Ex7,
    e_Page_ExMakefile,
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
void BuildLink(e_PageType PageID,const char *LinkTxt,char *outbuff,int MaxSize);

void Page_Index(void);
void Page_Links(void);
void Page_About(void);
void Page_Contact(void);
void Page_Downloads(void);
void Page_Examples(void);
void Page_Ex1(void);
void Page_Ex2(void);
void Page_Ex3(void);
void Page_Ex4(void);
void Page_Ex5(void);
void Page_Ex6(void);
void Page_Ex7(void);
void Page_ExMakefile(void);

void Page_MainCSS(void);
void Page_sport_soccer(void);

#endif
