--*****************************************************************************
--*	Author:		RJP Computing <rjpcomputing@gmail.com>
--*	Date:		12/15/2006
--*	Version:	1.00-beta
--*
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- wxWidgets version
local wx_ver = "28"
local wx_ver_minor = ""
local wx_custom = "_wxfb"

-- Set the name of your package.
package.name = "plotctrl"
-- Set this if you want a different name for your target than the package's name.
-- local targetName = ""

-- Set the files to include.
package.files = { matchfiles( "../../src/plotctrl/*.c*", "../../src/plotctrl/*.hh", "../../include/wx/plotctrl/*.h") }

-- Set the defines.
if ( options["shared"] ) then
	package.defines = { "MONOLITHIC", "WXMAKINGDLL_PLOTCTRL" }
end

MakeWxAdditionsPackage( package, "", wx_ver, wx_ver_minor, wx_custom )

-- gtk build/link options
if ( OS == "linux" ) then
	table.insert( package.config["Debug"].linkoptions, "-l`wx-config "..debug_option.." --basename`_things-`wx-config --release`"..wx_custom )
	table.insert( package.config["Release"].linkoptions, "-l`wx-config --basename`_things-`wx-config --release`"..wx_custom )
	table.insert( package.buildoptions, "`pkg-config gtk+-2.0 --cflags`" )
	table.insert( package.linkoptions, { "`pkg-config gtk+-2.0 --libs`", "-L../../lib" } )
end
