How to compile

Ubuntu

Needed software
    * gcc
    * GNU make
    * WebC

Installing
    Installing gcc & make
        sudo apt update
        sudo apt install build-essential

    Installing WebC
        wget http://webcprecompiler.com/Releases/Linux/WebCC.tar.gz
        tar -xzf WebCC.tar.gz
        cd WebC
        sudo ./install.sh

Compiling
    cd HelloWorld
    make -s

Windows
Windows do not use the makefiles.  This is keep things simpler.  You can use
the makefiles but you need GNU make and a version of GCC that works with
windows.

There are build.bat files in the directorys that compile using the TCC compiler.
You need to install 'gcc' and 'webcc' and have them in the path.

Needed software
    * gcc (http://www.mingw.org/wiki/Getting_Started)
    * WebC (http://webcprecompiler.com/)

Compiling.
    HelloWorld:
        cd HelloWorld
        build.bat

    Others:
        cd example_directory
        make -s
