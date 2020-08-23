#!/bin/bash
echo "***Globals"
cd Globals
make -s
cd ..

echo "***GraphicFiles"
cd GraphicFiles
make -s
cd ..

echo "***HelloWorld"
cd HelloWorld
make -s
cd ..

echo "***PageFunctions"
cd PageFunctions
make -s
cd ..

echo "***ShortEchoTag"
cd ShortEchoTag
make -s
cd ..

echo "***ShortTag"
cd ShortTag
make -s
cd ..

echo "***Strings"
cd Strings
make -s
cd ..
