/*******************************************************************************
 * FILENAME: WCWebAPI.h
 * 
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
 *
 * HISTORY:
 *    Paul Hutchinson (29 Oct 2019)
 *       Created
 *
 *******************************************************************************/
#ifndef __WCWEBAPI_H_
#define __WCWEBAPI_H_

/***  HEADER FILES TO INCLUDE          ***/

/***  DEFINES                          ***/

/***  MACROS                           ***/

/***  TYPE DEFINITIONS                 ***/

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/

/***  EXTERNAL FUNCTION PROTOTYPES     ***/
void wcecho(const char *buff);
void wcwrite(const unsigned char *bin,int Len);
void wcSetMine(const char *Mime);

#endif
