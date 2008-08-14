--*****************************************************************************
--*	Author:		RJP Computing <rjpcomputing@gmail.com>
--*	Date:		09/12/2007
--*	Version:	1.00
--*
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- wxWidgets version
local wx_ver = "28"
local wx_ver_minor = ""
local wx_custom = options["flavor"] or ""

-- Set the name of your package.
package.name = "treelistctrl"
-- Set this if you want a different name for your target than the package's name.
-- local targetName = ""

-- Set the files to include.
package.files = { matchfiles( "../../src/treelistctrl/*.cpp", "../../include/wx/treelistctrl/*.h") }

-- Set the defines.
if ( options["shared"] ) then
	package.defines = { "MONOLITHIC", "WXMAKINGDLL_TREELISTCTRL" }
end

MakeWxAdditionsPackage( package, "", wx_ver, wx_ver_minor, wx_custom )
