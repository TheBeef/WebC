/*******************************************************************************
 * FILENAME: CmdLine.c
 *
 * PROJECT:
 *    WebC
 *
 * FILE DESCRIPTION:
 *    This file has command line arg processing it in.
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
#include "CmdLine.h"
#include "SourceFiles.h"
#include "Options.h"
#include "Version.h"
#include <string.h>
#include <stdio.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

int ProcessArgs(int argv,char **argc)
{
    int r;
    int TotalFiles;

    for(r=1;r<argv;r++)
    {
        if(argc[r][0]=='-')
        {
            /* Option */
            if(strcmp(argc[r],"-o")==0)
            {
                /* Output filename */
                r++;
                if(r==argv)
                {
                    fprintf(stderr,"error: missing filename after '-o'\n");
                    return 1;
                }
                if(strlen(argc[r])>sizeof(g_Options.OutputFilename))
                {
                    fprintf(stderr,"error: Filename to long after '-o' "
                            "option\n");
                    return 1;
                }
                strcpy(g_Options.OutputFilename,argc[r]);
            }
            else if(strcmp(argc[r],"-x")==0)
            {
                /* force language */
                r++;
                if(r==argv)
                {
                    fprintf(stderr,"error: missing language after '-x'\n");
                    return 1;
                }
                if(strcasecmp(argc[r],"c")==0)
                    g_Options.ForceFileType=e_SourceFile_C;
                else if(strcasecmp(argc[r],"c++")==0)
                    g_Options.ForceFileType=e_SourceFile_C;
                else if(strcasecmp(argc[r],"wc")==0)
                    g_Options.ForceFileType=e_SourceFile_WC;
                else if(strcasecmp(argc[r],"bin")==0)
                    g_Options.ForceFileType=e_SourceFile_Binary;
                else if(strcasecmp(argc[r],"c-header")==0)
                    g_Options.ForceFileType=e_SourceFile_H;
                else
                {
                    fprintf(stderr,"error: unknown language '%s'\n",argc[r]);
                    return 1;
                }
            }
            else if(strcmp(argc[r],"-m")==0)
            {
                /* force mime type */
                r++;
                if(r==argv)
                {
                    fprintf(stderr,"error: missing mime type after '-m'\n");
                    return 1;
                }
                if(strlen(argc[r])>=sizeof(g_Options.ForcedMIMEType))
                {
                    fprintf(stderr,"error: mime type too long for internal "
                            "buffer\n");
                    return 1;
                }
                strcpy(g_Options.ForcedMIMEType,argc[r]);
            }
            else if(strcmp(argc[r],"--help")==0)
            {
                printf("Usage: webcc [options] file...\n");
                printf("Options:\n");
                printf("  --help                   Display this information.\n");
                printf("  --version                Displays WebC version information\n");
                printf("  -o <file>                Place the output into <file>.\n");
                printf("  -x <language>            Specify the language of the following input files.\n");
                printf("                           Supported values:\n");
                printf("                                c -- A C file\n");
                printf("                                c++ -- A C++ file\n");
                printf("                                wc -- A WebC file\n");
                printf("                                bin -- A binary file\n");
                printf("                                c-header -- A C header file\n");
                printf("  -m <mime type>           Overrides the auto detect of the mime type on binary files.\n");
            }
            else if(strcmp(argc[r],"--version")==0)
            {
                printf("WebC %s\n",WEBC_VERSION_STR);
                printf("Copyright (C) 2020 Paul Hutchinson.\n");
                printf("This is free software; see the source for copying conditions.  There is NO\n");
                printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
                return 0;
            }
            else
            {
                fprintf(stderr,"error: unrecognized command line option '%s'\n",
                        argc[r]);
                return 1;
            }
        }
        else
        {
            AddNewSourceFile(argc[r],g_Options.ForceFileType);
        }
    }

    /* Ok, check we all's still good */
    TotalFiles=GetSourceFileCount();

    if(TotalFiles==0)
    {
        fprintf(stderr,"error: no input files\n");
        return 1;
    }

    if(g_Options.OutputFilename[0]!=0)
    {
        /* We have an override of the output filename, we can only do one
           file */
        if(TotalFiles>1)
        {
            fprintf(stderr,"error: cannot specify -o with multiple files\n");
            return 1;
        }
    }

ShowList();

    return 0;
}

