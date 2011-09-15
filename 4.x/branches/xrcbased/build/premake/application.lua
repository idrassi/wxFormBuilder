project "wxFormBuilder"

    local wxVersion = _OPTIONS["wx_version"]

    kind            "WindowedApp"
    files           {"../../src/app/**.h", "../../src/app/**.hpp", "../../src/app/**.cpp", "../../src/app/**.xrc"}
    includedirs     {"../../src/corelib/include", "../../src/app"}
--  libdirs         {"../../sdk/lib"}
    defines         {"NO_GCC_PRAGMA", "SCI_NAMESPACE", "__WX__", "WXUSINGDLL_WXFBCORE"}
    links           {"wxFBCore"}

if wxVersion < "2.9" then
    includedirs     {"../../src/controls/include"}
    links           {"wxPropGrid", "wxScintilla"}
end

if os.get() == "windows" then
    files           {"../../src/app/**.rc"}
    targetdir       "../../output"
    defines         {"WIN32", "_WINDOWS"}
    buildoptions    {"-gstabs"}
    libdirs         {"../../output"}
    links           {"bfd", "intl", "iberty", "psapi", "imagehlp"}

elseif os.get() == "macosx" then
    excludes        {"**.rc"}
    libdirs         {"../../output/lib/wxformbuilder"}
    linkoptions     {"-L../../output/lib/wxformbuilder"}
    targetdir       "../../output/bin"
    targetname      "wxformbuilder"
else
    excludes        {"**.rc"}
    libdirs         {"../../output/lib/wxformbuilder"}
    targetdir       "../../output/bin"
    targetname      "wxformbuilder"

-- CodeLite and CodeBlocks link options
    local temp = "-Wl,-rpath,"

    if _ACTION == "codelite" then
        temp = temp .. "$$``ORIGIN/../lib/wxformbuilder"
    elseif _ACTION == "codeblocks" then
        temp = temp .. "$``ORIGIN/../lib/wxformbuilder"
    end

    linkoptions     { temp }
end

-- Release configuration
configuration "Release"
    buildoptions      {"-fno-strict-aliasing"}

if os.get() == "windows" then
    flags             {"Symbols"}
end
    wx_config         { Libs="all" }

-- Debug configuration
configuration "Debug"
    defines           {"__WXFB_DEBUG__"}
    wx_config         { Libs="all", Debug="yes" }

-- MacOSX configuration
configuration {"macosx", "Debug"}
    postbuildcommands {"../macosx/postbuildd.sh"}

configuration {"macosx", "Release"}
    postbuildcommands {"../macosx/postbuild.sh"}

