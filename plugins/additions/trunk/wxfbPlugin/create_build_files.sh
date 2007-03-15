#!/bin/sh
#
sdk/premake/premake-linux --target cb-gcc --unicode --with-wx-shared
echo done...
echo 
#
sdk/premake/premake-linux --target gnu --unicode --with-wx-shared
echo done...
echo 
#
echo Done generating all project files for wxAdditions Plugin.
#