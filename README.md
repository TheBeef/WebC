# WebC
WebC is a new open source C extension language that is especially suited for web development in the C programming language for embedded systems.

WebC is a pre-compiler that lets you embed HTML into C code (like PHP but with C).

Nice, but what does that mean? An example:

## Example #1 An introductory example
    <!DOCTYPE html>
    <html>
        <head>
            <title>Example</title>
        </head>
        <body>
            <?wc
                wcecho("Hi, I'm a WebC program!");
            ?>
        </body>
    </html>

Instead of lots of commands to output HTML (as seen in normal C), WebC pages contain HTML with embedded C code that does "something" (in this case, output "Hi, I'm a WebC program!"). The WebC code is enclosed in special start and end processing instructions <?wc and ?> that allow you to jump into and out of "C mode".

What distinguishes WebC from other script languages (like PHP) is that it is compiled C code (or C++ if you like that better). This is great for limited resource embedded applications where code size and speed are important.

The best thing in using WebC is that it makes working with HTML in C **bearable**.

You should check out the Examples to see how WebC is used.
