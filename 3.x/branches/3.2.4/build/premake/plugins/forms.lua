-----------------------------------------------------------------------------
--  Name:        forms.lua
--  Purpose:     Form controls plugin project build script.
--  Author:      Andrea Zanellato
--  Modified by: 
--  Created:     22/10/2011
--  Copyright:   (c) 2011 wxFormBuilder Team
--  Licence:     GNU General Public License Version 2
-----------------------------------------------------------------------------
project "forms-components-plugin"
    kind                "SharedLib"
    files               {"../../../plugins/layout/forms.cpp"}
    includedirs
    {
        "../../../sdk/tinyxml", "../../../sdk/plugin_interface"
    }
    defines             {"BUILD_DLL", "TIXML_USE_TICPP"}
    flags               {"ExtraWarnings"}
    links               {"TiCPP", "plugin-interface"}
    targetname          "forms"

    configuration "not windows"
        targetdir       "../../../output/lib/wxformbuilder"

    configuration "windows"
        targetprefix    "lib"
        targetdir       "../../../output/plugins/layout"

    configuration "Debug"
        wx_config       { Debug="yes" }

    configuration "Release"
        buildoptions    {"-fno-strict-aliasing"}
        wx_config       {}

