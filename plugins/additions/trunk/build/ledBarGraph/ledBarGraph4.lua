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
project( "ledbargraph" )
if _OPTIONS[ "shared-libraries" ] then
	kind	"SharedLib"
	defines	{ "MONOLITHIC", "WXMAKINGDLL_WXLEDBARGRAPH" }
else
	kind	"StaticLib"
end

function CommonSetup()
	defines			{}
	includedirs 	{ "../../include" }
	files			{ 
						"../../src/ledBarGraph/*.cpp",
						"../../include/wx/ledBarGraph/*.h",
					}
	Configure()
end

CommonSetup()
wx.Configure( true )
