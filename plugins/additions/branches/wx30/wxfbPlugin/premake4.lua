-- ----------------------------------------------------------------------------
--	Premake4 script to build wxFormBuilder Plugin.
--	Author:		Chris Steenwyk
--	Date:		Tue 19 November 2013
--	Version:	1.00
--
--	Notes:
-- ----------------------------------------------------------------------------

-- INCLUDES -------------------------------------------------------------------
--
dofile( "../build/premake/presets4.lua" )
dofile( "../build/premake/wxpresets4.lua" )

EnableOption( "force-32bit" )
EnableOption( "monolithic" )

-- PROJECT SETTINGS -----------------------------------------------------------
--
solution			"wxfbPlugin"
configurations 		{ "Release", "Debug" }
targetdir			"bin"

-- Add projects here.
dofile( "wxfbPlugin4.lua" )
dofile( "sdk/plugin_interface/plugin_interface4.lua" )
dofile( "sdk/tinyxml/ticpp4.lua" )
