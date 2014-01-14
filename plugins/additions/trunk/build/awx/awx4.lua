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
project( "awx" )
if _OPTIONS[ "shared-libraries" ] then
	kind	"SharedLib"
	defines	{ "MONOLITHIC" }
else
	kind	"StaticLib"
end

defines			{}
includedirs 	{ "../../include" }
files			{
					"../../src/awx/*.cpp",
					"../../include/wx/awx/*.h",
				}
targetsuffix( "" )

Configure()
wx.Configure( true )
