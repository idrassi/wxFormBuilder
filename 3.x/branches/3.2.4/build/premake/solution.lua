-----------------------------------------------------------------------------
--  Name:        solution.lua
--  Purpose:     Generic Premake 4 solution defining common configurations
--               for all projects it contains.
--  Author:      Andrea Zanellato
--  Modified by: 
--  Created:     19/10/2011
--  Copyright:   (c) 2011 wxFormBuilder Team
--  Licence:     GNU General Public License Version 2
-----------------------------------------------------------------------------
solution "Solution"
    language "C++"
    location            ( "../../build/" .. _ACTION )
    BuildDir            = solution().location
    CustomSuffix        = "_wxfb"
    local scriptDir     = os.getcwd()
    os.chdir( BuildDir )

    dofile( scriptDir .. "/wxwidgets.lua" )

    configurations      {"Debug", "Release"}

if wxCompiler == "gcc" and os.is("windows") then
--  flags               {"NoImportLib"}
end
if wxUseUnicode then
    flags               {"Unicode"}
    defines             {"UNICODE", "_UNICODE"}
end
    configuration "windows"
        defines         {"WIN32", "_WINDOWS"}

    configuration "Debug"
        targetsuffix    "d"
        defines         {"DEBUG", "_DEBUG"}
        flags           {"Symbols"}

    if wxCompiler == "gcc" then
        buildoptions    {"-O0"}
    end

    configuration "Release"
        defines         {"NDEBUG"}
        flags           {"OptimizeSpeed"}

    dofile( scriptDir .. "/ticpp.lua" )
    dofile( scriptDir .. "/plugin-interface.lua" )
    dofile( scriptDir .. "/wxflatnotebook.lua" )

if wxVersion < "2.9" then
    dofile( scriptDir .. "/wxpropgrid.lua" )
    dofile( scriptDir .. "/wxscintilla.lua" )
end
    dofile( scriptDir .. "/plugins/additional.lua" )
    dofile( scriptDir .. "/plugins/common.lua" )
    dofile( scriptDir .. "/plugins/containers.lua" )
    dofile( scriptDir .. "/plugins/forms.lua" )
    dofile( scriptDir .. "/plugins/layout.lua" )
    dofile( scriptDir .. "/plugins/wxadditions-mini.lua" )
    dofile( scriptDir .. "/wxformbuilder.lua" )
    dofile( scriptDir .. "/utilities.lua" )

