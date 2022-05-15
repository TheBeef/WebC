/*******************************************************************************
 * FILENAME: ProcessBin.c
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
 *    Paul Hutchinson (24 Oct 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "ProcessBin.h"
#include "Util.h"
#include "Options.h"
#include <stdio.h>
#include <string.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

int ProcessBinFile(struct SourceFile *SFile,const char *OutFileName)
{
    FILE *in;
    FILE *out;
    char fnName[256];
    char InputBuff[1000];
    int RC;
    int o;
    int bytes;
    int WrapCount;
    const char *MIME;

    RC=GetFnNameFromFilename(SFile,fnName,sizeof(fnName));
    if(RC>0)
        return RC;

    in=fopen(SFile->Filename,"rb");
    if(in==NULL)
    {
        fprintf(stderr,"error: Can't open input file %s\n",SFile->Filename);
        return 1;
    }

    out=fopen(OutFileName,"w");
    if(out==NULL)
    {
        fclose(in);
        fprintf(stderr,"error: Can't write to %s\n",OutFileName);
        return 1;
    }

    /* Guess the mime type based on extention */
    MIME="application/octet-stream";
    if(g_Options.ForcedMIMEType[0]==0)
    {
        if(SFile->FilenameExt!=NULL)
        {
            if(strcasecmp(SFile->FilenameExt,"png")==0)
                MIME="image/png";
            if(strcasecmp(SFile->FilenameExt,"pdf")==0)
                MIME="application/pdf";
            if(strcasecmp(SFile->FilenameExt,"css")==0)
                MIME="text/css";
            if(strcasecmp(SFile->FilenameExt,"html")==0)
                MIME="text/html";
            if(strcasecmp(SFile->FilenameExt,"js")==0)
                MIME="text/javascript";
            if(strcasecmp(SFile->FilenameExt,"apng")==0)
                MIME="image/apng";
            if(strcasecmp(SFile->FilenameExt,"bmp")==0)
                MIME="image/bmp";
            if(strcasecmp(SFile->FilenameExt,"gif")==0)
                MIME="image/gif";
            if(strcasecmp(SFile->FilenameExt,"svg")==0)
                MIME="image/svg+xml";
            if(strcasecmp(SFile->FilenameExt,"webp")==0)
                MIME="image/webp";
            if(strcasecmp(SFile->FilenameExt,"wav")==0)
                MIME="audio/wav";
            if(strcasecmp(SFile->FilenameExt,"avi")==0)
                MIME="video/x-msvideo";
            if(strcasecmp(SFile->FilenameExt,"bin")==0)
                MIME="application/octet-stream";
            if(strcasecmp(SFile->FilenameExt,"doc")==0)
                MIME="application/msword";
            if(strcasecmp(SFile->FilenameExt,"docx")==0)
                MIME="application/vnd.openxmlformats-officedocument.wordprocessingml.document";
            if(strcasecmp(SFile->FilenameExt,"gz")==0)
                MIME="application/gzip";
            if(strcasecmp(SFile->FilenameExt,"jar")==0)
                MIME="application/java-archive";
            if(strcasecmp(SFile->FilenameExt,"json")==0)
                MIME="application/json";
            if(strcasecmp(SFile->FilenameExt,"jsonld")==0)
                MIME="application/ld+json";
            if(strcasecmp(SFile->FilenameExt,"mp3")==0)
                MIME="audio/mpeg";
            if(strcasecmp(SFile->FilenameExt,"mpeg")==0)
                MIME="video/mpeg";
            if(strcasecmp(SFile->FilenameExt,"odp")==0)
                MIME="application/vnd.oasis.opendocument.presentation";
            if(strcasecmp(SFile->FilenameExt,"ods")==0)
                MIME="application/vnd.oasis.opendocument.spreadsheet";
            if(strcasecmp(SFile->FilenameExt,"odt")==0)
                MIME="application/vnd.oasis.opendocument.text";
            if(strcasecmp(SFile->FilenameExt,"oga")==0)
                MIME="audio/ogg";
            if(strcasecmp(SFile->FilenameExt,"ogv")==0)
                MIME="video/ogg";
            if(strcasecmp(SFile->FilenameExt,"otf")==0)
                MIME="font/otf";
            if(strcasecmp(SFile->FilenameExt,"ppt")==0)
                MIME="application/vnd.ms-powerpoint";
            if(strcasecmp(SFile->FilenameExt,"pptx")==0)
                MIME="application/vnd.openxmlformats-officedocument.presentationml.presentation";
            if(strcasecmp(SFile->FilenameExt,"rar")==0)
                MIME="application/x-rar-compressed";
            if(strcasecmp(SFile->FilenameExt,"rtf")==0)
                MIME="application/rtf";
            if(strcasecmp(SFile->FilenameExt,"swf")==0)
                MIME="application/x-shockwave-flash";
            if(strcasecmp(SFile->FilenameExt,"tar")==0)
                MIME="application/x-tar";
            if(strcasecmp(SFile->FilenameExt,"ttf")==0)
                MIME="font/ttf";
            if(strcasecmp(SFile->FilenameExt,"txt")==0)
                MIME="text/plain";
            if(strcasecmp(SFile->FilenameExt,"vsd")==0)
                MIME="application/vnd.visio";
            if(strcasecmp(SFile->FilenameExt,"woff")==0)
                MIME="font/woff";
            if(strcasecmp(SFile->FilenameExt,"woff2")==0)
                MIME="font/woff2";
            if(strcasecmp(SFile->FilenameExt,"xls")==0)
                MIME="application/vnd.ms-excel";
            if(strcasecmp(SFile->FilenameExt,"xlsx")==0)
                MIME="application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
            if(strcasecmp(SFile->FilenameExt,"xml")==0)
                MIME="application/xml";
            if(strcasecmp(SFile->FilenameExt,"zip")==0)
                MIME="application/zip";
            if(strcasecmp(SFile->FilenameExt,"7z")==0)
                MIME="application/x-7z-compressed";
            if(strcasecmp(SFile->FilenameExt,"tiff")==0 ||
                    strcasecmp(SFile->FilenameExt,"tif")==0)
            {
                MIME="image/tiff";
            }
            if(strcasecmp(SFile->FilenameExt,"ico")==0 ||
                    strcasecmp(SFile->FilenameExt,"cur")==0)
            {
                MIME="image/x-icon";
            }
            if(strcasecmp(SFile->FilenameExt,"jpg")==0 ||
                    strcasecmp(SFile->FilenameExt,"jpeg")==0 ||
                    strcasecmp(SFile->FilenameExt,"jfif")==0 ||
                    strcasecmp(SFile->FilenameExt,"pjpeg")==0 ||
                    strcasecmp(SFile->FilenameExt,"pjp")==0)
            {
                MIME="image/jpeg";
            }
        }
    }
    else
    {
        /* Use the override */
        MIME=g_Options.ForcedMIMEType;
    }

    fprintf(out,"/*** GENERATED CODE FROM %s ***/\n",SFile->Filename);
    fprintf(out,"#include \"WCWebAPI.h\"\n");
    fprintf(out,"\n");
    fprintf(out,"unsigned char m_BinData_%s[]=",fnName);
    fprintf(out,"{\n");
    fprintf(out,"   ");

    WrapCount=0;
    while((bytes=fread(InputBuff,1,sizeof(InputBuff),in))!=0)
    {
        for(o=0;o<bytes;o++)
        {
            WrapCount++;
            fprintf(out,"0x%02X",(unsigned char)InputBuff[o]);
            if(bytes==sizeof(InputBuff) || o!=bytes-1)
            {
                fprintf(out,",");
                if((WrapCount&15)==15)
                    fprintf(out,"\n   ");
            }
        }
    }
    if((WrapCount&15)!=15)
        fprintf(out,"\n");

    fprintf(out,"};\n");
    fprintf(out,"\n");
    fprintf(out,"void %s(void)\n",fnName);
    fprintf(out,"{\n");
    fprintf(out,"    wcSetMine(\"%s\");\n",MIME);
    fprintf(out,"    wcwrite(m_BinData_%s,%d);\n",fnName,WrapCount);
    fprintf(out,"}\n");

    fclose(in);
    fclose(out);

    return 0;
}
