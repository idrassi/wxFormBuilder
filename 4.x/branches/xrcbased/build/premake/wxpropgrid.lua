project "wxPropGrid"

    local wxVersion  = _OPTIONS["wx_version"]
    local wx_ver     = string.gsub(wxVersion, '%.', '')
    local wx_custom  = "_wxfb"
    local wx_target  = ""
    local useUnicode = true
    if _OPTIONS["disable-unicode"] and wxVersion < "2.9" then useUnicode = false end

    -- target name for libraries
    if os.get() == "windows" then
        wx_target = "wxmsw"
    elseif os.get() == "linux" then
        wx_target = "wx_gtk2"
    elseif os.get() == "macosx" then
        wx_target = "wx_mac"
    end

    -- unicode sign
    usign = ""
    if useUnicode then
        usign = "u" 
    end

    kind         "SharedLib"
    defines      { "WXMAKINGDLL_PROPGRID", "MONOLITHIC" }
    files        { "../../src/controls/src/propgrid/*.cpp", "../../src/controls/include/wx/propgrid/*.h" }
    includedirs  { "../../src/controls/include" }
    targetsuffix ( wxVersion .. wx_custom )

    -- Release configuration
    configuration "Release"
        buildoptions { "-fno-strict-aliasing" }
        targetname   ( wx_target .. usign .. "_propgrid-" )
        wx_config    { Libs="core" }

    -- Debug configuration
    configuration "Debug"
        defines      { "__WXFB_DEBUG__" }
        targetname   ( wx_target .. usign .. "d_propgrid-" )
        wx_config    { Libs="core", Debug="yes" }

    configuration "windows"
        targetdir    "../../output"

    configuration "linux or bsd"
        defines      { "GTK" }
        targetdir    "../../output/lib/wxformbuilder"

    configuration "macosx"
        targetdir    "../../output/lib/wxformbuilder"

