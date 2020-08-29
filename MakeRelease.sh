#!/bin/bash
echo Packing up the Linux release
cd PreCompiler
make -s clean
make -s
cd ..

# Build the examples tar
#tar -czf Examples.tar.gz Examples/README.txt Examples/stdio/README.txt Examples/stdio/AutoDoc/*.c Examples/stdio/AutoDoc/*.wc Examples/stdio/AutoDoc/*.h Examples/stdio/AutoDoc/makefile Examples/stdio/HelloWorld/build.sh Examples/stdio/HelloWorld/main.wc Examples/stdio/HelloWorld/WCWebAPI.h Examples/stdio/Common/* Examples/WebServer/buildall.sh Examples/WebServer/README.txt Examples/WebServer/Common/* Examples/WebServer/Globals/*.h Examples/WebServer/Globals/*.wc Examples/WebServer/Globals/makefile Examples/WebServer/GraphicFiles/*.h Examples/WebServer/GraphicFiles/*.wc Examples/WebServer/GraphicFiles/*.png Examples/WebServer/GraphicFiles/makefile Examples/WebServer/HelloWorld/*.wc Examples/WebServer/HelloWorld/*.h Examples/WebServer/HelloWorld/makefile Examples/WebServer/PageFunctions/*.h Examples/WebServer/PageFunctions/*.wc Examples/WebServer/PageFunctions/makefile Examples/WebServer/ShortEchoTag/*.h Examples/WebServer/ShortEchoTag/*.wc Examples/WebServer/ShortEchoTag/makefile Examples/WebServer/ShortTag/*.h Examples/WebServer/ShortTag/*.wc Examples/WebServer/ShortTag/makefile Examples/WebServer/Strings/*.h Examples/WebServer/Strings/*.wc Examples/WebServer/Strings/makefile
tar -czf Examples.tar.gz Examples

# ** Make linux exe tar
mkdir WebCC
cp PreCompiler/webcc WebCC
cp PreCompiler/install.sh WebCC
tar -czf WebCC.tar.gz WebCC

# ** Make website tar
tar -czf WebSite.tar.gz WebSite
