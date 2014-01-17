--*****************************************************************************
--*	Author:		Chris Steenwyk <csteenwyk@gmail.com>
--*	Date:		11/19/2013
--*	Version:	1.00
--*
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- GENERAL SETUP -------------------------------------------------------------
--
project			"wxAdditions_Plugin"
kind			"SharedLib"
targetname		"wxadditions"
targetprefix	"lib"
targetdir		"wxAdditions"

defines			{
					"TIXML_USE_TICPP",
					"BUILD_DLL",
				}
includedirs 	{
					"../include",
					"sdk/tinyxml",
					"sdk/plugin_interface"
				}
files			{
					"*.cpp",
					"*.h",
					"*.lua",
				}
libdirs			{
					"lib",
					"../lib"
				}
if os.is( "windows" ) then
	libdirs { "../lib/gcc" .. _OPTIONS["compiler-version"] .. "_dll" }
end
links			{
					"plugin-interface",
					"TiCPP",
					wx.LibName( "treelistctrl", isDebug, true ),
					wx.LibName( "plotctrl", isDebug, true ),
					wx.LibName( "things", isDebug, true ),
					wx.LibName( "awx", isDebug, true ),
					wx.LibName( "ledbargraph", isDebug, true ),
					wx.LibName( "flatnotebook", isDebug, true ),
				}

Configure()
wx.Configure( false )


