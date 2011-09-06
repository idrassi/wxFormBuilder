#!/bin/sh

# Parse command line options
wxroot=""
for args in "$@"
do
    haveroot=`expr "${args}" : '--wx_root=.*'`
    if ( [ ${args} = "--help" ] || [ ${args} = "-h" ] ); then
        echo "Available options:"
        echo
#       echo "--disable-mediactrl       disable wxMediaCtrl in wx media library"
#       echo
        echo "--disable-unicode         disable unicode build"
        echo "                          (make an ansi build if wxversion <= 2.8, ignored otherwise.)"
        echo
        echo "--wx_root=path/to/wx/dir  Specify the wx-config path if"
        echo "                          wxWidgets is not installed in system"
        echo
        exit
#   elif [ ${args} = "--disable-mediactrl" ]; then
#       mediactrl="--disable-mediactrl"
#       continue
    elif [ ${args} = "--disable-unicode" ]; then
        unicode="--disable-unicode"
        continue
    elif ( [ "$haveroot" -gt "0" ] ); then
        wxroot=${args}
        continue
    fi
done

# Autodetect wxWidgets version
if [ "$wxroot" = "" ]; then
    wxver=`wx-config --version`
else
    wxpath=${wxroot#-*=}
    wxver=`$wxpath/wx-config --version`
fi

wxversion="--wx_version="`expr substr $wxver 1 3`

# Autodetect OS
isbsd=`expr "$unamestr" : '.*BSD'`
platform="unknown"
unamestr=$(uname)

if ( [ "$isbsd" -gt "0" ] ); then
    platform="bsd"
elif [ "$unamestr" = "Linux" ]; then
    platform="linux"
elif [ "$unamestr" = "Darwin" ]; then
    platform="macosx"
fi

# Build premake
cd build
make CONFIG=Release -C./premake4/$platform

#./premake/$platform/bin/release/premake4 --file=./premake/solution.lua $unicode $wxroot $wxversion $mediactrl codeblocks
./premake/$platform/bin/release/premake4 --file=./premake/solution.lua $unicode $wxroot $wxversion codelite
./premake/$platform/bin/release/premake4 --file=./premake/solution.lua $unicode $wxroot $wxversion gmake

#if [ "$platform" = "macosx" ]; then
#   ./premake4/macosx/bin/release/premake4 --file=./premake4/solution.lua xcode3
#fi

