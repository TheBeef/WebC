/* Back to back code doesn't seem to be working:
    code ?><?wc more code
*/

/*******************************************************************************
 * FILENAME: ProcessWebC2.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
 *
 * CREATED BY:
 *    Paul Hutchinson (30 Oct 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "ProcessWebC.h"
#include "Util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/
typedef enum
{
    e_CodeBlock_echoHTML,
    e_CodeBlock_cstringHTML,
    e_CodeBlock_C,
    e_CodeBlockMAX
} e_CodeBlockType;

struct FileBlocks
{
    e_CodeBlockType CodeType;
    long Start;
    long End;
    int Scope;
    bool QuickPrint;
    struct FileBlocks *Next;
};

/*** FUNCTION PROTOTYPES      ***/
static bool AddFileBlock2List(e_CodeBlockType CodeType,long Start,long End,
        int Scope,bool QuickPrint);
static void FreeAllFileBlocks(void);
static bool AnalyzeFile(FILE *in);
void WalkFileBlocks(FILE *in);

/*** VARIABLE DEFINITIONS     ***/
struct FileBlocks *m_FirstFileBlock=NULL;
struct FileBlocks *m_LastFileBlock=NULL;
char m_LineBuffer[10000];
char m_OutputBuffer[10000*2];     // Needs to be 2 times bigger than 'm_LineBuffer' (for C string escaping of chars)

int ProcessWebCFile(struct SourceFile *SFile,const char *OutFileName)
{
    FILE *in;
    FILE *out;
    char fnName[256];
    int RC;
    struct FileBlocks *Block;
    long BytesLeft;
    int bytes;
    int BlockSize;
    bool InPageFn;
    bool InPageFnSuppressed;
    const char *s;
    char *d;

    RC=GetFnNameFromFilename(SFile,fnName,sizeof(fnName));
    if(RC>0)
        return RC;

    in=fopen(SFile->Filename,"r");
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

    /* Find out about the <? blocks */
    AnalyzeFile(in);

//WalkFileBlocks(in);

    fprintf(out,"/*** GENERATED CODE FROM %s ***/\n",SFile->Filename);
    fprintf(out,"#include \"WCWebAPI.h\"\n");
    fflush(out);

    InPageFn=false;
    InPageFnSuppressed=false;

    for(Block=m_FirstFileBlock;Block!=NULL;Block=Block->Next)
    {
        fseek(in,Block->Start,SEEK_SET);

        if(Block->CodeType==e_CodeBlock_C)
        {
            /* Just copy the C code without changing anything */
            if(Block->QuickPrint)
            {
                fprintf(out,"    wcecho(");
                fflush(out);
            }
            BytesLeft=Block->End-Block->Start;
            while(BytesLeft>0)
            {
                BlockSize=BytesLeft;
                if(BlockSize>sizeof(m_LineBuffer))
                    BlockSize=sizeof(m_LineBuffer);
                bytes=fread(m_LineBuffer,1,BlockSize,in);
                if(bytes!=BlockSize)
                {
                    fprintf(stderr,"error: read error reading '%s' didn't get "
                            "expected number of bytes.",SFile->Filename);
                    fclose(in);
                    fclose(out);
                    return 1;
                }
                bytes=fwrite(m_LineBuffer,1,BlockSize,out);
                if(bytes!=BlockSize)
                {
                    fprintf(stderr,"error: write error writing to '%s'.",
                            OutFileName);
                    fclose(in);
                    fclose(out);
                    return 1;
                }
                BytesLeft-=BlockSize;
            }
            if(Block->QuickPrint)
            {
                fprintf(out,");\n");
                fflush(out);
            }
        }
        else if(Block->CodeType==e_CodeBlock_echoHTML ||
                Block->CodeType==e_CodeBlock_cstringHTML)
        {
            /* This is an HTML block. */
            if(Block->CodeType==e_CodeBlock_echoHTML)
            {
                if(!InPageFn && !InPageFnSuppressed)
                {
                    if(Block->Scope!=0)
                    {
                        InPageFnSuppressed=true;
                    }
                    else
                    {
                        fprintf(out,"void %s(void)\n",fnName);
                        fprintf(out,"{\n");
                        InPageFn=true;
                    }
                }
                fprintf(out,"    wcecho(\"");
                fflush(out);
            }
            else
            {
                fprintf(out,"\"");
                fflush(out);
            }

            /* Copy this HTML block.  It will need to be converted to a C
               string  */
            BytesLeft=Block->End-Block->Start;
            while(BytesLeft>0)
            {
                BlockSize=BytesLeft;
                if(BlockSize>sizeof(m_LineBuffer))
                    BlockSize=sizeof(m_LineBuffer);
                bytes=fread(m_LineBuffer,1,BlockSize,in);
                if(bytes!=BlockSize)
                {
                    fprintf(stderr,"error: read error reading '%s' didn't get "
                            "expected number of bytes.",SFile->Filename);
                    fclose(in);
                    fclose(out);
                    return 1;
                }
                /* Esc all the C control chars and handle end of lines */
                d=m_OutputBuffer;
                for(s=m_LineBuffer;s<m_LineBuffer+BlockSize;s++)
                {
                    /* Remove \r's */
                    if(*s=='\r')
                        continue;

                    if(*s=='\n')
                    {
                        fwrite(m_OutputBuffer,1,d-m_OutputBuffer,out);
                        d=m_OutputBuffer;
                        fprintf(out,"\\n\"\n");
                        fprintf(out,"        \"");
                        fflush(out);
                        continue;
                    }
                    if(*s=='\\' || *s=='\'' || *s=='\"')
                        *d++='\\';
                    *d++=*s;
                }

                /* Write out the output buffer */
                fwrite(m_OutputBuffer,1,d-m_OutputBuffer,out);
                d=m_OutputBuffer;

                BytesLeft-=BlockSize;
            }
            if(Block->CodeType==e_CodeBlock_echoHTML)
                fprintf(out,"\");\n");
            else
                fprintf(out,"\"");
            fflush(out);
        }
        else
        {
            fprintf(stderr,"error: internal error.  Parser in unknown state.");
            fclose(in);
            fclose(out);
            return 2;
        }
    }

    if(InPageFn)
    {
        /* We are still in the page function close it off */
        fprintf(out,"}\n");
        fflush(out);
        InPageFn=false;
    }

    fclose(in);
    fclose(out);


    FreeAllFileBlocks();

    return 0;
}

static bool AnalyzeFile(FILE *in)
{
    int bytes;
    bool InCMode;
    bool InLineComment;
    bool InStr;
    bool InComment;
    int CommentEscPoint;
    int EscPoint;
    const char *CurPos;
    int r;
    long Offset;
    long StartOfLastBlock;
    long StartOfEscSeq;
    long EscSeqLen;
    char c;
    bool SkipNewLine;
    int Scope;
    bool QuickPrint;
    bool EndBlock;
    bool NextBlockIsCString;
    e_CodeBlockType EndingBlockType;

    InCMode=false;
    InLineComment=false;
    InStr=false;
    InComment=false;
    CommentEscPoint=0;
    EscPoint=0;
    Offset=0;
    StartOfLastBlock=0;
    StartOfEscSeq=0;
    SkipNewLine=false;
    Scope=0;
    QuickPrint=false;
    NextBlockIsCString=false;

    while((bytes=fread(m_LineBuffer,1,sizeof(m_LineBuffer),in))>0)
    {
        CurPos=m_LineBuffer;
        for(r=0;r<bytes;r++,Offset++)
        {
            c=*CurPos++;

//printf("%c,%d,%d\n",c<32?'.':c,InCMode,EscPoint);

            /* Ignore \r */
            if(c=='\r')
                continue;

            if(SkipNewLine)
            {
                SkipNewLine=false;
                if(c=='\n')
                {
                    /* Skip this new line */
                    StartOfLastBlock=Offset+1;
                    continue;
                }
            }

            if(InCMode)
            {
                /* C code */
                if(InLineComment)
                {
                    /* Only end of line can get us back out */
                    if(c=='\n')
                        InLineComment=false;
                }
                else
                {
                    if(!InStr)
                    {
                        if(!InComment)
                        {
                            if(c=='{')
                                Scope++;

                            if(c=='}')
                            {
                                Scope--;
                                if(Scope<0)
                                    Scope=0;
                            }

                            switch(CommentEscPoint)
                            {
                                case 0: // Looking for '/'
                                    if(c=='/')
                                        CommentEscPoint++;
                                break;
                                case 1: // Looking for '*' or '/'
                                    if(c=='*')
                                        InComment=true;
                                    if(c=='/')
                                        InLineComment=true;
                                    CommentEscPoint=0;
                                break;
                            }

                            EndBlock=false;
                            switch(EscPoint)
                            {
                                case 0: // Looking for '?' or '='
                                    NextBlockIsCString=false;
                                    if(c=='?' || c=='=')
                                    {
                                        EscPoint++;
                                        StartOfEscSeq=Offset;
                                    }
                                    if(c=='=')
                                    {
                                        NextBlockIsCString=true;
                                    }
                                break;
                                case 1: // Looking for '>' or '?'
                                    if(c=='>')
                                        EndBlock=true;
                                    else if(c=='?')
                                        EscPoint++;
                                    else
                                        EscPoint=0;
                                break;
                                case 2: // Looking for '>'
                                    if(c=='>')
                                        EndBlock=true;
                                break;
                            }
                            if(EndBlock)
                            {
                                /* Offset-1 because we don't want
                                   to count the ?> and Offset is at
                                   the ? */
                                EscSeqLen=Offset-StartOfEscSeq;
                                if(Offset-EscSeqLen-StartOfLastBlock>0)
                                {
                                    if(!AddFileBlock2List(e_CodeBlock_C,
                                            StartOfLastBlock,Offset-
                                            EscSeqLen,Scope,QuickPrint))
                                    {
                                        return false;
                                    }
                                }
                                StartOfLastBlock=Offset+1;  // Skip the ?>
                                InCMode=false;
                                SkipNewLine=true;
                                QuickPrint=false;
                            }
                        }
                        else
                        {
                            switch(CommentEscPoint)
                            {
                                case 0: // Looking for '*'
                                    if(c=='*')
                                        CommentEscPoint++;
                                break;
                                case 1: // Looking for '/'
                                    if(c=='/')
                                        InComment=false;
                                    CommentEscPoint=0;
                                break;
                            }
                        }
                    }
                    if(!InComment && c=='\"')
                        InStr^=true;
                }
            }
            else
            {
                /* HTML mode */
                switch(EscPoint)
                {
                    case 0: // Looking for '<'
                        if(c=='<')
                        {
                            EscPoint++;
                            StartOfEscSeq=Offset;
                        }
                    break;
                    case 1: // Looking for '?'
                        if(c=='?')
                            EscPoint++;
                        else
                            EscPoint=0;
                    break;
                    case 2: // Looking for white space, 'w', or '='
                        if(c=='\t' || c==' ' || c=='\n' || c=='=')
                        {
                            if(c=='=')
                                QuickPrint=true;
                            if(NextBlockIsCString)
                                EndingBlockType=e_CodeBlock_cstringHTML;
                            else
                                EndingBlockType=e_CodeBlock_echoHTML;

                            EscSeqLen=Offset-StartOfEscSeq;
                            if(Offset-EscSeqLen-StartOfLastBlock>0)
                            {
                                if(!AddFileBlock2List(EndingBlockType,
                                        StartOfLastBlock,Offset-EscSeqLen,
                                        Scope,false))
                                {
                                    return false;
                                }
                            }
                            StartOfLastBlock=Offset+1;
                            InCMode=true;
                            EscPoint=0;
                        }

                        if(c=='w')
                            EscPoint++;
                        else
                            EscPoint=0;
                    break;
                    case 3: // Looking for 'c'
                        if(c=='c')
                            EscPoint++;
                        else
                            EscPoint=0;
                    break;
                    case 4: // Looking for white space
                        if(c==' ' || c=='\t' || c=='\n')
                        {
                            if(NextBlockIsCString)
                                EndingBlockType=e_CodeBlock_cstringHTML;
                            else
                                EndingBlockType=e_CodeBlock_echoHTML;

                            EscSeqLen=Offset-StartOfEscSeq;
                            if(Offset-EscSeqLen-StartOfLastBlock>0)
                            {
                                if(!AddFileBlock2List(EndingBlockType,
                                        StartOfLastBlock,Offset-EscSeqLen,
                                        Scope,false))
                                {
                                    return false;
                                }
                            }
                            InCMode=true;
                            StartOfLastBlock=Offset+1;
                        }
                        EscPoint=0;
                    break;
                }
            }
        }
    }

    /* Ok, handle the final block */
    if(StartOfLastBlock!=Offset)
    {
        if(InCMode)
        {
            if(!AddFileBlock2List(e_CodeBlock_C,StartOfLastBlock,Offset,Scope
                    ,false))
            {
                return false;
            }
        }
        else
        {
            if(!AddFileBlock2List(e_CodeBlock_echoHTML,StartOfLastBlock,Offset,
                    Scope,false))
            {
                return false;
            }
        }
    }

    return true;
}

static bool AddFileBlock2List(e_CodeBlockType CodeType,long Start,long End,
        int Scope,bool QuickPrint)
{
    struct FileBlocks *NewFileBlock;

    NewFileBlock=malloc(sizeof(struct FileBlocks));
    if(NewFileBlock==NULL)
        return false;

    NewFileBlock->CodeType=CodeType;
    NewFileBlock->Start=Start;
    NewFileBlock->End=End;
    NewFileBlock->Scope=Scope;
    NewFileBlock->QuickPrint=QuickPrint;
    NewFileBlock->Next=NULL;

    if(m_FirstFileBlock==NULL)
    {
        m_FirstFileBlock=NewFileBlock;
        m_LastFileBlock=NewFileBlock;
    }
    else
    {
        m_LastFileBlock->Next=NewFileBlock;
        m_LastFileBlock=NewFileBlock;
    }

    return true;
}

static void FreeAllFileBlocks(void)
{
    struct FileBlocks *tmp;

    while(m_FirstFileBlock!=NULL)
    {
        tmp=m_FirstFileBlock->Next;
        free(m_FirstFileBlock);
        m_FirstFileBlock=tmp;
    }
    m_FirstFileBlock=NULL;
    m_LastFileBlock=NULL;
}

char bbb[1000000];
void WalkFileBlocks(FILE *in)
{
    struct FileBlocks *p;
    const char *BlockName;
    int r;
    char c;

    for(p=m_FirstFileBlock;p!=NULL;p=p->Next)
    {
        switch(p->CodeType)
        {
            case e_CodeBlock_echoHTML:
                BlockName="Echo HTML";
            break;
            case e_CodeBlock_cstringHTML:
                BlockName="CString HTML";
            break;
            case e_CodeBlock_C:
                BlockName="C";
            break;
            default:
                BlockName="Unknown";
            break;
        }
        printf("\33[33;1m%s\33[0;33m block from %ld to %ld, Scope:%d, QuickPrint:%d\33[0m\n",BlockName,p->Start,p->End,p->Scope,p->QuickPrint);
        switch(p->CodeType)
        {
            case e_CodeBlock_echoHTML:
                printf("\33[31;1m");
            break;
            case e_CodeBlock_cstringHTML:
                printf("\33[0;31m");
            break;
            case e_CodeBlock_C:
                printf("\33[32;1m");
            break;
            default:
                printf("\33[34;1m");
            break;
        }
        fseek(in,p->Start,SEEK_SET);
        fread(bbb,1,p->End-p->Start,in);
        bbb[p->End-p->Start]=0;
        printf("    ");
        for(r=0;r<p->End-p->Start;r++)
        {
            c=bbb[r];
            printf("%c",c);
            if(c=='\n')
                printf("    ");
        }
        if(c=='\n')
            printf("\r");
        else
            printf("\n");
//        printf("%s",bbb);
        printf("\33[0m");
    }
}
