/* TODO:
    * Web Engine(s)
        x stdio
        x BittyHTTP
        * CGI
    * Binary to C
    * Write Supporting files (main.c, pages.c)
    * Standard functions????
        * wcecho()
        * wcwrite()
        * wcSetMime()
        GET[]?
        POST[]?
        COOKIE[]?
        HEADERS[]?

Block Rules:
    * System starts in HTML mode
    * <? ?> at top is global space
    * any HTML goes into page function unless the C scope is > 0
*/
#include <stdio.h>
#include "CmdLine.h"
#include "TimeStamp.h"
#include "Options.h"
#include "SourceFiles.h"
#include "ProcessFile.h"

int main(int argv,char **argc)
{
    int RetValue;
    struct SourceFile *Cur;

    RetValue=ProcessArgs(argv,argc);
    if(RetValue>0)
        return RetValue;

    for(Cur=g_FirstSourceFile;Cur!=NULL;Cur=Cur->Next)
    {
//        printf("Processing %s\n",Cur->Filename);
        Process(Cur);
    }

    return 0;
}
