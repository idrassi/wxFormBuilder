-- A solution contains projects, and defines the available configurations
solution "wxFormBuilder"

    language "C++"
    configurations {"Release", "Debug"}
    location       ("../../build/" .. _ACTION)
    flags          {"ExtraWarnings"}

newoption  {
    trigger     =  "disable-unicode",
    description =  "disable unicode build (make an ansi build if needed)"
}

newoption  {
    trigger     =  "wx_version",
    description =  "wxWidgets version (e.g. 2.8, 2.9)"
}

    local useUnicode = true
    local wxVersion  = _OPTIONS["wx_version"]
    local scriptDir  = os.getcwd()
    local buildDir   = solution().location
    os.chdir( buildDir )

    if _OPTIONS["disable-unicode"] and wxVersion < "2.9" then useUnicode = false end

    if _OPTIONS["disable-unicode"] and wxVersion > "2.8" then
        print("wxWidgets version is " .. wxVersion .. ": --disable-unicode will be ignored.")
    end

    if useUnicode then defines { "UNICODE", "_UNICODE" } end

-- Release configuration (global)
    configuration "Release"
        defines      { "NDEBUG" }
        flags        { "OptimizeSpeed" }

-- Debug configuration (global)
    configuration "Debug"
        targetsuffix "d"
        defines      { "DEBUG", "_DEBUG" }
        flags        { "Symbols" }
        buildoptions { "-O0" }

    dofile( scriptDir .. "/wxwidgets.lua" )

    if wxVersion < "2.9" then
        dofile( scriptDir .. "/wxpropgrid.lua" )
        dofile( scriptDir .. "/wxscintilla.lua" )
    end
    dofile( scriptDir .. "/project.lua" )
    dofile( scriptDir .. "/wxfbutils.lua" )

