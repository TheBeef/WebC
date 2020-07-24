/*******************************************************************************
 * FILENAME: SourceFiles.c
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
 *    Paul Hutchinson (23 Oct 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "SourceFiles.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/
struct SourceFile *g_FirstSourceFile=NULL;
struct SourceFile *m_LastSourceFile=NULL;

bool AddNewSourceFile(const char *Filename,e_SourceFileType OverrideFileType)
{
    struct SourceFile *NewSourceFile;
    char *p;

    NewSourceFile=malloc(sizeof(struct SourceFile));
    if(NewSourceFile==NULL)
    {
        printf("Out of memory\n");
        return false;
    }

    NewSourceFile->Filename=malloc(strlen(Filename)+1);
    if(NewSourceFile->Filename==NULL)
    {
        free(NewSourceFile);
        printf("Out of memory\n");
        return false;
    }

    strcpy(NewSourceFile->Filename,Filename);
    NewSourceFile->FilenameExt=NULL;
    NewSourceFile->FileType=OverrideFileType;
    NewSourceFile->Next=NULL;

    /* Find the extention */
    p=NewSourceFile->Filename+strlen(NewSourceFile->Filename);
    while(p>NewSourceFile->Filename)
    {
        if(*p=='.')
            break;
        p--;
    }
    if(p!=NewSourceFile->Filename)
        NewSourceFile->FilenameExt=p+1;

    if(OverrideFileType==e_SourceFileMAX)
    {
        if(NewSourceFile->FilenameExt!=NULL)
        {
            if(strcasecmp(NewSourceFile->FilenameExt,"wc")==0)
                NewSourceFile->FileType=e_SourceFile_WC;
            else if(strcasecmp(NewSourceFile->FilenameExt,"c")==0)
                NewSourceFile->FileType=e_SourceFile_C;
            else if(strcasecmp(NewSourceFile->FilenameExt,"cxx")==0)
                NewSourceFile->FileType=e_SourceFile_C;
            else if(strcasecmp(NewSourceFile->FilenameExt,"cc")==0)
                NewSourceFile->FileType=e_SourceFile_C;
            else if(strcasecmp(NewSourceFile->FilenameExt,"cp")==0)
                NewSourceFile->FileType=e_SourceFile_C;
            else if(strcasecmp(NewSourceFile->FilenameExt,"c++")==0)
                NewSourceFile->FileType=e_SourceFile_C;
            else if(strcasecmp(NewSourceFile->FilenameExt,"cpp")==0)
                NewSourceFile->FileType=e_SourceFile_C;
            else if(strcasecmp(NewSourceFile->FilenameExt,"h")==0)
                NewSourceFile->FileType=e_SourceFile_H;
            else if(strcasecmp(NewSourceFile->FilenameExt,"hpp")==0)
                NewSourceFile->FileType=e_SourceFile_H;
            else if(strcasecmp(NewSourceFile->FilenameExt,"hh")==0)
                NewSourceFile->FileType=e_SourceFile_H;
            else if(strcasecmp(NewSourceFile->FilenameExt,"hp")==0)
                NewSourceFile->FileType=e_SourceFile_H;
            else if(strcasecmp(NewSourceFile->FilenameExt,"h++")==0)
                NewSourceFile->FileType=e_SourceFile_H;
            else if(strcasecmp(NewSourceFile->FilenameExt,"tcc")==0)
                NewSourceFile->FileType=e_SourceFile_H;
            else
                NewSourceFile->FileType=e_SourceFile_Binary;
        }
        else
        {
            NewSourceFile->FileType=e_SourceFile_Binary;
        }
    }

    /* Link in */
    if(m_LastSourceFile==NULL)
    {
        g_FirstSourceFile=NewSourceFile;
        m_LastSourceFile=NewSourceFile;
    }
    else
    {
        m_LastSourceFile->Next=NewSourceFile;
        m_LastSourceFile=NewSourceFile;
    }
    return true;
}

int GetSourceFileCount(void)
{
    int Total;
    struct SourceFile *Cur;

    Total=0;
    for(Cur=g_FirstSourceFile;Cur!=NULL;Cur=Cur->Next)
        Total++;
    return Total;
}

void ShowList(void)
{
    struct SourceFile *Cur;
    for(Cur=g_FirstSourceFile;Cur!=NULL;Cur=Cur->Next)
    {
//        printf("LOOK:%s",Cur->Filename);
//        if(Cur->FilenameExt!=NULL)
//            printf(" (%s)",Cur->FilenameExt);
//        printf(" (%d)\n",Cur->FileType);
    }
}
