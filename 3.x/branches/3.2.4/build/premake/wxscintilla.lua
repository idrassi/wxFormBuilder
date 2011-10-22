-----------------------------------------------------------------------------
--  Name:        wxscintilla.lua
--  Purpose:     wxScintilla library build script for wxWidgets 2.8.
--  Author:      Andrea Zanellato
--  Modified by: 
--  Created:     19/10/2011
--  Copyright:   (c) 2011 wxFormBuilder Team
--  Licence:     GNU General Public License Version 2
-----------------------------------------------------------------------------
project "wxScintilla"
    kind                "SharedLib"
    defines
    {
        "WXMAKINGDLL_SCI","LINK_LEXERS","SCI_LEXER","SCI_NAMESPACE","__WX__"
    }
    files
    {
        "../../src/controls/src/wxScintilla/*.cpp",
        "../../src/controls/include/wx/wxScintilla/*.h",
        "../../src/controls/src/wxScintilla/scintilla/**.cxx",
        "../../src/controls/src/wxScintilla/scintilla/**.h"
    }
    includedirs
    {
        "../../src/controls/include", "../../src/controls/src/wxScintilla",
        "../../src/controls/src/wxScintilla/scintilla/include",
        "../../src/controls/src/wxScintilla/scintilla/src"
    }
    targetsuffix        ( wxVersion .. CustomSuffix )

    configuration "linux or bsd"
        defines         {"GTK"}
        targetdir       "../../output/lib/wxformbuilder"

    configuration "macosx"
        targetdir       "../../output/lib/wxformbuilder"

    configuration "windows"
        links           {"Gdi32"}
        targetdir       "../../output"

    configuration "Release"
        buildoptions    {"-fno-strict-aliasing"}
        targetname      ( wxTarget .. wxUnicodeSign .. "_scintilla-" )
        wx_config       { Libs="core" }

    configuration "Debug"
        targetname      ( wxTarget .. wxUnicodeSign .. "d_scintilla-" )
        wx_config       { Libs="core", Debug="yes" }
