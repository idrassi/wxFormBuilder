#!/bin/bash

function CheckAndMakeDir
{
	if [ ! -d $1 ]
	then
		mkdir $1
	fi
}

outputDir=""

if [ ! -n "$1" ]
then
 echo "Please specify output directory."
 exit
else
 outputDir=$1
fi  
  
CheckAndMakeDir $outputDir
CheckAndMakeDir $outputDir/share
CheckAndMakeDir $outputDir/share/wxformbuilder
CheckAndMakeDir $outputDir/share/wxformbuilder/plugins
  
cp -R --interactive --verbose ../../wxAdditions $outputDir/share/wxformbuilder/plugins/
cp -R --interactive --verbose ../../../lib/gcc_dll/*.so $outputDir/share/wxformbuilder/plugins/wxAdditions

exit

