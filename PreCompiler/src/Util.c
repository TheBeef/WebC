/*******************************************************************************
 * FILENAME: Util.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
 *
 * CREATED BY:
 *    Paul Hutchinson (28 Oct 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "Util.h"
#include <string.h>
#include <stdio.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

int GetFnNameFromFilename(struct SourceFile *SFile,char *FnName,int MaxFnName)
{
    char *e;
    char *s;

    /* Build a page function name for this file */
    if(SFile->FilenameExt!=NULL)
        e=SFile->FilenameExt-1;
    else
        e=&SFile->Filename[strlen(SFile->Filename)];
    /* Search from the end to find the start of the filename */
    s=e-1;
    while(s>=SFile->Filename)
    {
        if((*s>='a' && *s<='z') || (*s>='A' && *s<='Z') || (*s>='0' && *s<='9')
                || *s=='_')
        {
            /* Valid char */
            s--;
        }
        else
        {
            /* End of the filename (and or acceptable chars) */
            if(*s!='/' && *s!='\\' && *s!=':')
            {
                fprintf(stderr,"error: Filename %s contains char's that are "
                        "not part of a valid C function name "
                        "(%c is invalid).\n",SFile->Filename,*s);
                return 1;
            }
            break;
        }
    }
    /* Copy the filename */
    if(e-s-1>MaxFnName)
    {
        fprintf(stderr,"error: Internal buffer overflow making page "
                "function name.  Filename can only be %d bytes in length\n",
                MaxFnName);
        return 1;
    }
    strcpy(FnName,"Page_");
    FnName[strlen(FnName)+e-s-1]=0;
    memcpy(&FnName[strlen(FnName)],s+1,e-s-1);

    return 0;
}
