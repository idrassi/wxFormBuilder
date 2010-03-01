#!/bin/sh
#

set -e

# Build premake
PREMAKE_DIR=sdk/premake
make CONFIG=Release -C$PREMAKE_DIR/src -f../build/Makefile

unicode="--unicode"

$PREMAKE_DIR/bin/premake --target cl-gcc $unicode $debug --with-wx-shared $1
echo done...
echo
#
#$PREMAKE_DIR/bin/premake --target cb-gcc $unicode $debug --with-wx-shared $1
#echo done...
#echo
#
$PREMAKE_DIR/bin/premake --target gnu $unicode $debug --with-wx-shared $1
echo done...
echo
#
echo Done generating all project files for wxFormBuilder.
#
