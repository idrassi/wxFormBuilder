-- Create dynamically Plugins projects
local plugins = { "additional", "common", "containers", "forms", "layout" }
for _, pluginName in ipairs( plugins ) do
    local plugin     = pluginName .. "-components-plugin"
    local prj        = project( plugin )
    local targetDir

if os.get() == "windows" then
    targetDir    =  "../../output/plugins/" .. pluginName
else
    targetDir    =  "../../output/lib/wxformbuilder"
end
    kind         "SharedLib"
    objdir       = buildDir
    targetdir    ( targetDir )
    targetname   ( pluginName )
    files        { "../../plugins/" .. pluginName .. "/*.cpp", "../../plugins/" .. pluginName .. "/*.h" }
    includedirs  { "../../sdk/tinyxml", "../../sdk/plugin_interface" }
    defines      { "__WX__", "BUILD_DLL", "TIXML_USE_TICPP" }

-- Release configuration
configuration "Release"
    buildoptions { "-fno-strict-aliasing" }
    links        { "fbPluginInterface", "ticpp" }
    wx_config    {}

-- Debug configuration
configuration "Debug"
    defines      { "__WXFB_DEBUG__" }
    links        { "fbPluginInterfaced", "ticppd" }
    wx_config    { Debug="yes" }

-- Windows configuration
configuration "windows"
    defines      { "WIN32", "_WINDOWS" }
    targetprefix ( "lib" )

configuration "not windows"
    libdirs      { "../../output/lib/wxformbuilder", "../../sdk/lib" }

end
--    local prjs = solution().projects
--    for i, prj in ipairs(prjs) do
--        print(prj.name)
--    end
