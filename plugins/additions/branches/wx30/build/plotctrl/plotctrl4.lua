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
project( "plotctrl" )
if _OPTIONS[ "shared-libraries" ] then
	kind	"SharedLib"
	defines	{ "MONOLITHIC", "WXMAKINGDLL_PLOTCTRL" }
else
	kind	"StaticLib"
end

function CommonSetup()
	defines			{}
	includedirs 	{ "../../include" }
	files			{ 
						"../../src/plotctrl/*.cpp",
						"../../src/plotctrl/*.c",
						"../../include/wx/plotctrl/*.h",
						"../../src/plotctrl/*.hh",
					}
	links			{ "things" }
	Configure()
end

CommonSetup()
wx.Configure( true )
