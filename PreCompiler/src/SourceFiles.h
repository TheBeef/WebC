/*******************************************************************************
 * FILENAME: SourceFiles.h
 * 
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
 *
 * HISTORY:
 *    Paul Hutchinson (23 Oct 2019)
 *       Created
 *
 *******************************************************************************/
#ifndef __SOURCEFILES_H_
#define __SOURCEFILES_H_

/***  HEADER FILES TO INCLUDE          ***/
#include <stdbool.h>

/***  DEFINES                          ***/

/***  MACROS                           ***/

/***  TYPE DEFINITIONS                 ***/
typedef enum
{
    e_SourceFile_WC,
    e_SourceFile_C,
    e_SourceFile_H,
    e_SourceFile_Binary,
    e_SourceFileMAX
} e_SourceFileType;

struct SourceFile
{
    char *Filename;
    char *FilenameExt;
    e_SourceFileType FileType;
    struct SourceFile *Next;
};

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/
extern struct SourceFile *g_FirstSourceFile;

/***  EXTERNAL FUNCTION PROTOTYPES     ***/
bool AddNewSourceFile(const char *Filename,e_SourceFileType FileType);
int GetSourceFileCount(void);
void ShowList(void);

#endif
