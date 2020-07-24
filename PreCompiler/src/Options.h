/*******************************************************************************
 * FILENAME: Options.h
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
#ifndef __OPTIONS_H_
#define __OPTIONS_H_

/***  HEADER FILES TO INCLUDE          ***/
#include "SourceFiles.h"
#include <stdbool.h>

/***  DEFINES                          ***/

/***  MACROS                           ***/

/***  TYPE DEFINITIONS                 ***/
struct Options
{
    char OutputFilename[256];
    char OutputExt[256];            // The extention we take on to our output
    e_SourceFileType ForceFileType; // What file to force the input to be processed as
    char ForcedMIMEType[256];       // If we are forcing the mime type for bin files this will be it
};

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/
extern struct Options g_Options;

/***  EXTERNAL FUNCTION PROTOTYPES     ***/

#endif
