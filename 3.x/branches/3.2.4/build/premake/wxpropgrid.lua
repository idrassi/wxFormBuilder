-----------------------------------------------------------------------------
--  Name:        wxpropgrid.lua
--  Purpose:     wxPropertyGrid library build script for wxWidgets 2.8.
--  Author:      Andrea Zanellato
--  Modified by: 
--  Created:     19/10/2011
--  Copyright:   (c) 2011 wxFormBuilder Team
--  Licence:     GNU General Public License Version 2
-----------------------------------------------------------------------------
project "wxPropertyGrid"
    kind                "SharedLib"
    defines             {"WXMAKINGDLL_PROPGRID"}
    files
    {
        "../../src/controls/src/propgrid/*.cpp",
        "../../src/controls/include/wx/propgrid/*.h"
    }
    flags               {"ExtraWarnings"}
    includedirs         {"../../src/controls/include"}
    targetsuffix        ( wxVersion .. CustomSuffix )

    configuration "not windows"
        targetdir       "../../output/lib/wxformbuilder"

    configuration "windows"
        targetdir       "../../output"

    configuration "Release"
        buildoptions    {"-fno-strict-aliasing"}
        targetname      ( wxTarget .. wxUnicodeSign .. "_propgrid-" )
        wx_config       { Libs="core,adv,xrc" }

    configuration "Debug"
        targetname      ( wxTarget .. wxUnicodeSign .. "d_propgrid-" )
        wx_config       { Libs="core,adv,xml,xrc", Debug="yes" }
