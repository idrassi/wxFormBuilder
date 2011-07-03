project "plugin_interface"

	language					"C++"
	kind        				"StaticLib"
	targetname 					"fbPluginInterface"
	targetdir	 				"../../sdk/lib/"
	files						{ "../../sdk/plugin_interface/**.cpp", "../../sdk/plugin_interface/**.h" }
	includedirs 				{ "../../sdk/tinyxml" }
	libdirs 					{ "../../sdk/lib" }
	defines						{ "__WX__", "WXUSINGDLL", "TIXML_USE_TICPP", "UNICODE", "_UNICODE" }
	flags						{ "ExtraWarnings", "Unicode" }

	if os.get() == "windows" then
		defines					{ "WIN32", "_WINDOWS" }
	else
		excludes				{ "**.rc" }
		buildoptions			{ "-fPIC" }
	end

	configuration "vs*"
		-- Windows and Visual C++ 2005/2008
		defines			{ "_CRT_SECURE_NO_DEPRECATE" }

	configuration "Debug"
		targetsuffix 	"d"
		buildoptions	{ "-O0", "`$(29xDebug)/wx-config --debug=yes --cflags`" }
		linkoptions		{ "`$(29xDebug)/wx-config --debug=yes --libs all`" }
		flags 			{ "Symbols" }
		defines			{ "DEBUG", "_DEBUG", "__WXDEBUG__", "__WXFB_DEBUG__" }
		links 			{ "ticppd" }

	configuration "Release"
		buildoptions 	{ "-fno-strict-aliasing", "`$(29xRelease)/wx-config --debug=no --cflags`" }
		linkoptions		{ "`$(29xRelease)/wx-config --debug=no --libs all`" }
		flags			{ "OptimizeSpeed" }
		defines			{ "NDEBUG" }
		links 			{ "ticpp" }

