/*******************************************************************************
 * FILENAME: ProcessFile.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
 *
 * CREATED BY:
 *    Paul Hutchinson (24 Oct 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "ProcessFile.h"
#include "ProcessWebC.h"
#include "ProcessBin.h"
#include "Options.h"
#include <stdio.h>
#include <string.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/
int Process(struct SourceFile *SFile)
{
    char OutFileName[256];
    int ExtSize;

    ExtSize=strlen(g_Options.OutputExt);

    if(strlen(SFile->Filename)>sizeof(OutFileName)-ExtSize)
    {
        fprintf(stderr,"error: filename to long (%s)\n",SFile->Filename);
        return 1;
    }

    if(g_Options.OutputFilename[0]!=0)
    {
        strcpy(OutFileName,g_Options.OutputFilename);
    }
    else
    {
        strcpy(OutFileName,SFile->Filename);
        if(SFile->FilenameExt!=NULL)
            OutFileName[SFile->FilenameExt-SFile->Filename-1]=0;
        strcat(OutFileName,g_Options.OutputExt);
    }

    switch(SFile->FileType)
    {
        case e_SourceFile_WC:
            return ProcessWebCFile(SFile,OutFileName);
        break;
        case e_SourceFile_C:
        case e_SourceFile_H:
            /* We don't do any processing on these */
        break;
        case e_SourceFile_Binary:
            return ProcessBinFile(SFile,OutFileName);
        break;
        case e_SourceFileMAX:
        break;
    }
    return 0;
}
