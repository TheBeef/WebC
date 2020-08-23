/*******************************************************************************
 * FILENAME: CollectInfo.c
 *
 * PROJECT:
 *    WebC
 *
 * FILE DESCRIPTION:
 *    This file collects info for the auto doc.  It's a normal C file.
 *
 * COPYRIGHT:
 *    Copyright (c) 2020 Paul Hutchinson
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *    
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 *
 * CREATED BY:
 *    Paul Hutchinson (22 Aug 2020)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "CollectInfo.h"
#include "HelperFunctions.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

bool CollectInfoForAutoDoc(struct AutoDocInfo *Info)
{
    char *FnName;
    char WorkStr[300];
    char *FnNameEnd;
    char *RetType;
    char *EndOfRetType;
    char *ArgNameStart;
    char *ArgNameEnd;
    int arg;
    char *NextDescPos;
    char io[10];
    bool Done;
    int r;
    int Len;

    printf("Auto fill in the data? ");
    fflush(stdout);
    fgets(io,sizeof(io),stdin);
    if(io[0]=='y' || io[0]=='Y')
    {
        strcpy(Info->Prototype,"uint8_t StealMoney(const char *userName,uint16_t amount,struct AccountSpec *destAccount,struct falseTrail *falseTrail);");
        strcpy(Info->FnName,"StealMoney");
        Info->ArgCount=4;

        strcpy(Info->Args[0].Name,"userName");
        strcpy(Info->Args[1].Name,"amount");
        strcpy(Info->Args[2].Name,"destAccount");
        strcpy(Info->Args[3].Name,"falseTrail");

        Info->Args[0].Dir="I";
        Info->Args[1].Dir="I";
        Info->Args[2].Dir="I";
        Info->Args[3].Dir="I";

        Info->Args[0].Desc="Name to make the transaction under.  Popular favorites include \"Ronald Reagan\" and \"Mohamar Quadaffi\".";
        Info->Args[1].Desc="Number of dollars to transfer (in thousands).";
        Info->Args[2].Desc="A filled-in AccountSpec structure detailing the destination account (see financial/accounts.h).  If NULL, a second Great Depression will be triggered.";
        Info->Args[3].Desc="If the DA_FALSETRAIL bit is set in the destAccount, a falseTrail structure must be provided.";

        strcpy(Info->FnDescriptionBuff,"Transfer money from the Federal Reserve Bank into the specified interest-earning checking account. No records of the transaction will be retained.\n\n"
            "NOTE: Do not run on Tuesdays!\n\n"
            "Known bugs: Old versions of this function would occasionally print the address and home phone number of the caller on local police 976 terminals. We are confident that this problem has been resolved.");

        strcpy(Info->ReturnDesc,"Zero for success, else an error code is returned (see financial/errors.h).");

        return true;
    }

    printf("Function prototype:\n");
    fgets(Info->Prototype,sizeof(Info->Prototype)-1,stdin);

    strcpy(WorkStr,Info->Prototype);

    FnNameEnd=strchr(WorkStr,'(');
    if(FnNameEnd==NULL)
    {
        printf("Failed to find name of function\n");
        return false;
    }

    *FnNameEnd=0;

    FnName=FnNameEnd-1;

    /* Back up until we are no long in the function name */
    while(FnName>WorkStr && IsWhileSpace(*FnName))
        FnName--;
    if(FnName==WorkStr)
    {
        printf("Failed to find name of function\n");
        return false;
    }

    while(FnName>WorkStr && IsValidCNameChar(*FnName))
        FnName--;
    if(FnName==WorkStr)
    {
        printf("Failed to find name of function\n");
        return false;
    }
    EndOfRetType=FnName;
    FnName++;

    /* Skip white space */
    while(EndOfRetType>WorkStr && IsWhileSpace(*EndOfRetType))
        EndOfRetType--;
    if(EndOfRetType==WorkStr)
    {
        printf("Failed to find the end of the return type\n");
        return false;
    }
    EndOfRetType++;
    *EndOfRetType=0;    // If there isn't a while space between the fn name and return type this will kill it, but we don't care so we don't worry about it
    RetType=WorkStr;

    arg=0;
    if(strncmp(FnNameEnd+1,"void",4)!=0)
    {
        ArgNameEnd=FnNameEnd+1;
        Done=false;
        while(arg<sizeof(Info->Args)/sizeof(struct ArgInfo) && !Done)
        {
            /* Find the end of the next arg */
            while(*ArgNameEnd!=0 && *ArgNameEnd!=',' && *ArgNameEnd!=')')
            {
                ArgNameEnd++;
            }
            if(*ArgNameEnd==0)
            {
                printf("Failed to find the end of an arg\n");
                return false;
            }
            if(*ArgNameEnd==')')
                Done=true;
            *ArgNameEnd=0;

            /* Ok, now we have the end of the arg, find the start */
            ArgNameStart=ArgNameEnd-1;
            while(*ArgNameStart!=0 && IsValidCNameChar(*ArgNameStart))
                ArgNameStart--;
            if(*ArgNameStart==0)
            {
                printf("Failed to find the start of an arg\n");
                return false;
            }
            ArgNameStart++;

            strncpy(Info->Args[arg].Name,ArgNameStart,sizeof(Info->Args[arg].Name)-1);
            Info->Args[arg].Name[sizeof(Info->Args[arg].Name)-1]=0;
            arg++;

            ArgNameEnd++;   // Move to the start of the next arg
        }
    }

    NextDescPos=Info->ArgDescriptionBuff;
    for(r=0;r<arg;r++)
    {
        printf("Argument \"%s\":\n",Info->Args[r].Name);
        printf("    is an [I]nput / [O]utput / [B]oth (in/out):");
        fflush(stdout);
        fgets(io,sizeof(io)-1,stdin);
        switch(toupper(io[0]))
        {
            default:
            case 'I':
                Info->Args[r].Dir="I";
            break;
            case 'O':
                Info->Args[r].Dir="O";
            break;
            case 'B':
                Info->Args[r].Dir="I/O";
            break;
        }
        printf("    Input the description for this argument:");
        fflush(stdout);
        fgets(NextDescPos,sizeof(Info->ArgDescriptionBuff)-
                (NextDescPos-Info->ArgDescriptionBuff)-1,stdin);
        Info->Args[r].Desc=NextDescPos;
        Len=strlen(NextDescPos);
        if(NextDescPos[Len-1]=='\n')
        {
            NextDescPos[Len-1]=0;
            Len--;
        }
        NextDescPos+=Len+1;
        if(NextDescPos>Info->ArgDescriptionBuff+
                sizeof(Info->ArgDescriptionBuff)-1)
        {
            printf("out of memory for arg description\n");
            return false;
        }
    }

    printf("Function description (enter . on a blank line to end):\n");
    NextDescPos=Info->FnDescriptionBuff;
    for(;;)
    {
        fgets(NextDescPos,sizeof(Info->FnDescriptionBuff)-
                (NextDescPos-Info->FnDescriptionBuff)-1,stdin);

        if(strcmp(NextDescPos,".\n")==0)
        {
            *NextDescPos=0;
            break;
        }
        NextDescPos+=strlen(NextDescPos);

        if(NextDescPos>Info->FnDescriptionBuff+
                sizeof(Info->FnDescriptionBuff)-1)
        {
            printf("out of memory for function description\n");
            return false;
        }
    }

    if(strcmp(RetType,"void")!=0)
    {
        printf("Enter a description of the return value:\n");
        fgets(Info->ReturnDesc,sizeof(Info->ReturnDesc),stdin);
    }
    else
    {
        strcpy(Info->ReturnDesc,"NONE");
    }

    strcpy(Info->FnName,FnName);
    Info->ArgCount=arg;

    return true;
}

