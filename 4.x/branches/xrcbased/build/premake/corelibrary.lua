project "wxFBCore"

    local wxVersion  = _OPTIONS["wx_version"]
    local wx_ver     = string.gsub(wxVersion, '%.', '')
    local useUnicode = true
    if _OPTIONS["disable-unicode"] and wxVersion < "2.9" then useUnicode = false end

    -- unicode sign
    usign = ""

if useUnicode then
    usign = "u" 
end

    kind         "SharedLib"
    defines      {"WXMAKINGDLL_WXFBCORE"}
    files        {"../../src/corelib/src/**.cpp", "../../src/corelib/include/**.h"}
    includedirs  {"../../src/corelib/include"}
    targetsuffix ( wxVersion )

if os.get() == "windows" then
    libdirs      {"../../output"}
else
    libdirs      {"../../output/lib/wxformbuilder"}
end

if wxVersion < "2.9" then
    links       {"wxPropGrid", "wxScintilla"}
    includedirs {"../../src/controls/include"}
end
    -- Release configuration
    configuration "Release"
        buildoptions { "-fno-strict-aliasing" }
        targetname   ( "wxformbuilder" .. usign .. "_" )
        wx_config    { Libs="core" }

    -- Debug configuration
    configuration "Debug"
        defines      { "__WXFB_DEBUG__" }
        targetname   ( "wxformbuilder" .. usign .. "d_" )
        wx_config    { Libs="core", Debug="yes" }

    configuration "windows"
        targetdir    "../../output"

    configuration "linux or bsd"
--      defines      { "GTK" }
        targetdir    "../../output/lib/wxformbuilder"

    configuration "macosx"
        targetdir    "../../output/lib/wxformbuilder"

