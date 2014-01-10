--*****************************************************************************
--*	Author:		Chris Steenwyk <csteenwyk@gmail.com>
--*	Date:		11/13/2013
--*	Version:	1.00
--*
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- GENERAL SETUP -------------------------------------------------------------
--
project( "things" )
if _OPTIONS[ "shared-libraries" ] then
	kind	"SharedLib"
	defines	{ "MONOLITHIC", "WXMAKINGDLL_THINGS" }
else
	kind	"StaticLib"
end

function CommonSetup()
	defines			{}
	includedirs 	{ "../../include" }
	files			{
						"../../src/things/*.cpp",
						"../../include/wx/things/*.h",
					}
	excludes 		{
						"../../src/things/matrix2d.*",
						"../../include/wx/things/matrix2d.h",
					}
	Configure()
	targetsuffix( "" )
end

CommonSetup()
wx.Configure( true )
