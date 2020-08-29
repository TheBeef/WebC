/*******************************************************************************
 * FILENAME: ReleaseNotes.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    This file has the release notes in it.  This is also a change log.
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
 * CREATED BY:
 *    Paul Hutchinson (19 Aug 2020)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "ReleaseNotes.h"

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

//static struct ReleaseNote m_Notes_Next[]=
//{
//    {
//         "Title",
//         "Description"
//    },
//};

static struct ReleaseNote m_Notes_1_0[]=
{
    {
        "First Version",
         "This is the first version."
    },
};

const struct ReleaseInfo m_ReleaseNotes[]=
{
    {"1.0","29 Aug 2020","First Release",m_Notes_1_0,sizeof(m_Notes_1_0)/sizeof(struct ReleaseNote)},
};

const unsigned long m_ReleaseNoteCount=sizeof(m_ReleaseNotes)/sizeof(struct ReleaseInfo);
