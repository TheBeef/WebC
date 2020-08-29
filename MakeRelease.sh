#!/bin/bash
echo This should be run a fresh checkout of the repo as it moves files around and makes a general mess

tar czf WebCCSource.tar.gz PreCompiler

echo Packing up the Linux release
cd PreCompiler
make -s clean
make -s
cd ..

# Build the examples tar
tar -czf Examples.tar.gz Examples

# ** Make linux exe tar
mkdir WebCC
cp PreCompiler/webcc WebCC
cp PreCompiler/install.sh WebCC
tar -czf WebCC.tar.gz WebCC

# ** Make website tar
mkdir WebSiteSource
cp -r WebSite/ WebSiteSource/
cp ReleaseNotes.c WebSiteSource
cp ReleaseNotes.h WebSiteSource
tar -czf WebSite.tar.gz WebSiteSource

mkdir ReleaseFiles
mv Examples.tar.gz ReleaseFiles
mv WebCC.tar.gz ReleaseFiles
mv WebSite.tar.gz ReleaseFiles
mv WebCCSource.tar.gz ReleaseFiles

echo Done
