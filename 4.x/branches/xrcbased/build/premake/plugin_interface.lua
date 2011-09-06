project "plugin_interface"

    kind         "StaticLib"
    targetname   "fbPluginInterface"
    targetdir    "../../sdk/lib/"
    files        { "../../sdk/plugin_interface/**.cpp", "../../sdk/plugin_interface/**.h" }
    includedirs  { "../../sdk/tinyxml" }
    libdirs      { "../../sdk/lib/" }
    defines      { "TIXML_USE_TICPP" }

configuration "not windows"
    excludes     { "**.rc" }
    buildoptions { "-fPIC" }

-- Release configuration
configuration "Release"
    buildoptions { "-fno-strict-aliasing" }
    links        { "ticpp" }
    wx_config    {}

-- Debug configuration
configuration "Debug"
    defines      { "__WXFB_DEBUG__" }
    links        { "ticppd" }
    wx_config    { Debug="yes" }

