#!/bin/bash
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

mkdir /opt/WebC &> /dev/null
cp webcc /opt/WebC
chmod a+x /opt/WebC/webcc
ln -s /opt/WebC/webcc /usr/bin/webcc &> /dev/null

echo Installed
