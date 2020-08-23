How to compile

Ubuntu

Needed software
    You will need:
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
???
