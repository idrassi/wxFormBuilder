-- ----------------------------------------------------------------------------
--	Premake4 script to build wxAdditions.
--	Author:		Chris Steenwyk
--	Date:		Wed 13 November 2013
--	Version:	1.00
--
--	Notes:
-- ----------------------------------------------------------------------------

-- INCLUDES -------------------------------------------------------------------
--
dofile( "premake/presets4.lua" )
dofile( "premake/wxpresets4.lua" )

-- PROJECT SETTINGS -----------------------------------------------------------
--
solution			"wxAdditions"
configurations 		{ "Release", "Debug" }
targetdir			"bin"

EnableOption( "unicode" )

if os.is( "linux" ) then
	EnableOption( "wx-shared" )
end

-- Add projects here.
dofile( "awx/awx4.lua" )
dofile( "things/things4.lua" )
dofile( "plotctrl/plotctrl4.lua" )
dofile( "ledBarGraph/ledBarGraph4.lua" )
dofile( "wxFlatNotebook/wxFlatNotebook4.lua" )
dofile( "treelistctrl/treelistctrl4.lua" )
