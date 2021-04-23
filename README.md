# WebC
WebC is a new open source C extension language that is especially suited for web development in the C programming language for embedded systems. It is C code embedded into HTML markup, that is then converted to standard C code, and then compiled with a normal C compiler.

An example is worth a 1000 words so:

## Example #1 An introductory example

We start with a WebC program. This is a mix of HTML and C code.

example.wc:

    <?wc
    #include <stdio.h>
    
    int i;
    char buff[100];
    ?>
    <!DOCTYPE html>
    <html>
        <head>
            <title>WebC</title>
        </head>
        <body>
            <h1>Hi, I'm a WebC program!</h1>
            <pre>
            <?wc
                for(i=1;i<12;i++)
                {
                    sprintf(buff,"%d x 9 = %d\n",i,i*9);
                    wcecho(buff);
                }
            ?>
            </pre>
        </body>
    </html>

We then compile this with WebC using webcc example.wc, which makes the following C code.

example.c:

    /*** GENERATED CODE FROM example.wc ***/
    #include "WCWebAPI.h"
    #include <stdio.h>
    
    int i;
    char buff[100];
    
    void Page_example(void)
    {
        wcecho("<!DOCTYPE html>\n"
            "<html>\n"
            "    <head>\n"
            "        <title>WebC</title>\n"
            "    </head>\n"
            "    <body>\n"
            "        <h1>Hi, I\'m a WebC program!</h1>\n"
            "        <pre>\n"
            "        ");
        for(i=1;i<12;i++)
        {
            sprintf(buff,"%d x 9 = %d\n",i,i*9);
            wcecho(buff);
        }
        wcecho("        </pre>\n"
            "    </body>\n"
            "</html>\n"
            "");
    }

Next we compile the example.c file with a standard C compiler (you do need to provide the main(), wcecho() and WCWebAPI.h for it to link).

When we run the executable it will output in the following HTML:

    <!DOCTYPE html>
    <html>
        <head>
            <title>WebC</title>
        </head>
        <body>
            <h1>Hi, I'm a WebC program!</h1>
            <pre>
                1 x 9 = 9
                2 x 9 = 18
                3 x 9 = 27
                4 x 9 = 36
                5 x 9 = 45
                6 x 9 = 54
                7 x 9 = 63
                8 x 9 = 72
                9 x 9 = 81
                10 x 9 = 90
                11 x 9 = 99
            </pre>
        </body>
    </html>

##Tada!

As you can see instead of lots of commands to output HTML (as seen in normal C), WebC pages contain HTML with embedded C code that does "something" (in this case, output the nine times table). The WebC code is enclosed in special start and end processing instructions <?wc and ?> that allow you to jump into and out of "C mode".

What distinguishes WebC from other script languages (like PHP) is that it is compiled C code (or C++ if you like that better). This is great for limited resource embedded applications where code size and speed are important.

The best thing in using WebC is that it makes working with HTML in C **bearable**.

See the web site for documentation, examples, and more at <a href='http://webcprecompiler.com/'>http://webcprecompiler.com/</a>.

##Support files

Here are the support files needed to make the above example actually compile and run. It only prints the output to stdout but by changing wcecho() you can do anything you like with it.

main.c

    #include <stdio.h>
    
    void Page_example(void);
    
    int main(void)
    {
        Page_example();
        return 0;
    }
    
    void wcecho(const char *str)
    {
        printf("%s",str);
    }

WCWebAPI.h

    void wcecho(const char *str);
