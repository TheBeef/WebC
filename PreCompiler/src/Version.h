/*******************************************************************************
 * FILENAME: Version.h
 * 
 * PROJECT:
 *    WebC
 *
 * FILE DESCRIPTION:
 *    This file the version of the precompiler in it.
 *
 * COPYRIGHT:
 *    Copyright (C) 2020  Paul Hutchinson
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
 *    Paul Hutchinson (19 Aug 2020)
 *       Created
 *
 *******************************************************************************/
#ifndef __VERSION_H_
#define __VERSION_H_

/***  HEADER FILES TO INCLUDE          ***/

/***  DEFINES                          ***/
#define WEBC_VERSION_MAJOR       1
#define WEBC_VERSION_MINOR       0
#define WEBC_VERSION_BUILD       0
#define WEBC_VERSION_BRANCH      0

#define WEBC_VERSION ((WEBC_VERSION_MAJOR<<24) | \
                    (WEBC_VERSION_MINOR<<16) | \
                    (WEBC_VERSION_BUILD<<8)  | \
                    (WEBC_VERSION_BRANCH))

#define VER_STR_HELPER(x) #x
#define VER_STR(x) VER_STR_HELPER(x)

#define WEBC_VERSION_STR  VER_STR(WEBC_VERSION_MAJOR) "." VER_STR(WEBC_VERSION_MINOR) "."  VER_STR(WEBC_VERSION_BUILD) "."  VER_STR(WEBC_VERSION_BRANCH)

/***  MACROS                           ***/

/***  TYPE DEFINITIONS                 ***/

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/

/***  EXTERNAL FUNCTION PROTOTYPES     ***/

#endif
