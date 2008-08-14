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
local wx_custom = options["flavor"] or ""

-- Set the name of your package.
package.name = "awx"
-- Set this if you want a different name for your target than the package's name.
-- local targetName = ""

-- Set the files to include.
package.files = { matchfiles( "../../src/awx/*.cpp", "../../include/wx/awx/*.h") }

-- Set the defines.
if ( options["shared"] ) then
	package.defines = { "MONOLITHIC" }
end

MakeWxAdditionsPackage( package, "", wx_ver, wx_ver_minor, wx_custom )
