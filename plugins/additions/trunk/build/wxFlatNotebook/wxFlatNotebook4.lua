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
project( "flatnotebook" )
if _OPTIONS[ "shared-libraries" ] then
	kind	"SharedLib"
	defines	{ "MONOLITHIC", "WXMAKINGDLL_FNB" }
else
	kind	"StaticLib"
end

function CommonSetup()
	defines			{}
	includedirs 	{ "../../include" }
	files			{
						"../../src/wxFlatNotebook/*.cpp",
						"../../include/wx/wxFlatNotebook/*.h",
					}
	Configure()
	targetsuffix( "" )
end

CommonSetup()
wx.Configure( true )

