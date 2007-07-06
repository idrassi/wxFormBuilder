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
package.name = "scintilla"
-- Set this if you want a different name for your target than the package's name.
-- local targetName = ""

-- Set the files to include.
package.files = { matchfiles( "../../src/wxScintilla/*.c*", "../../include/wx/wxScintilla/*.h") }

-- Set the defines.
if ( options["shared"] ) then
	package.defines = { "MONOLITHIC", "WXMAKINGDLL_SCI", "LINK_LEXERS", "SCI_LEXER" }
end

package.includepaths = { "../../src/wxScintilla", "../../src/wxScintilla/scintilla/include", "../../src/wxScintilla/scintilla/src" }

if ( OS == "linux" ) then
	table.insert( package.defines, { "GTK" } )
end

MakeWxAdditionsPackage( package, "", wx_ver, wx_ver_minor, wx_custom )
