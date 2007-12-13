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
CheckAndMakeDir $outputDir/lib
CheckAndMakeDir $outputDir/lib/wxformbuilder
  
cp -R --interactive ../../wxAdditions $outputDir/share/wxformbuilder/plugins/
mv $outputDir/share/wxformbuilder/plugins/wxAdditions/*.so $outputDir/lib/wxformbuilder/
cp -R --interactive ../../../lib/*.so $outputDir/lib/wxformbuilder/
rm -f $outputDir/lib/wxformbuilder/*flatnotebook*
rm -f $outputDir/lib/wxformbuilder/*propgrid*
rm -f $outputDir/lib/wxformbuilder/*cintilla*

exit

