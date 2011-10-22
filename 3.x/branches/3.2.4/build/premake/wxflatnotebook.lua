-----------------------------------------------------------------------------
--  Name:        wxflatnotebook.lua
--  Purpose:     wxFlatNotebook library build script.
--  Author:      Andrea Zanellato
--  Modified by: 
--  Created:     21/10/2011
--  Copyright:   (c) 2011 wxFormBuilder Team
--  Licence:     GNU General Public License Version 2
-----------------------------------------------------------------------------
project "wxFlatNotebook"
    kind            "SharedLib"
    defines         {"WXMAKINGDLL_FNB"}
    files
    {
        "../../src/controls/src/wxFlatNotebook/*.cpp",
        "../../src/controls/include/wx/wxFlatNotebook/*.h"
    }
    flags           {"ExtraWarnings"}
    includedirs     {"../../src/controls/include"}
    targetsuffix    ( wxVersion .. CustomSuffix )

    configuration "windows"
        targetdir    "../../output"

    configuration "not windows"
        targetdir    "../../output/lib/wxformbuilder"

    configuration "Release"
        buildoptions { "-fno-strict-aliasing" }
        targetname   ( wxTarget .. wxUnicodeSign .. "_flatnotebook-" )
        wx_config    { Libs="core,xrc" }

    configuration "Debug"
        targetname   ( wxTarget .. wxUnicodeSign .. "d_flatnotebook-" )
        wx_config    { Libs="core,xrc", Debug="yes" }
