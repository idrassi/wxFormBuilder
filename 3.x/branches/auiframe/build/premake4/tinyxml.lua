project "TiCPP"

	language					"C++"
	kind        				"StaticLib"
	targetname 					"ticpp"
	targetdir	 				"../../sdk/lib/"
	files						{ "../../sdk/tinyxml/**.cpp", "../../sdk/tinyxml/**.h" }
	libdirs 					{ "../../sdk/lib" }
	excludes					{ "xmltest.cpp" }
	defines						{ "TIXML_USE_TICPP", "UNICODE", "_UNICODE" }
	flags						{ "ExtraWarnings", "Unicode" }

	if os.get() == "windows" then
		defines					{ "WIN32", "_WINDOWS" }
	else
		excludes				{ "**.rc" }
		buildoptions			{ "-fPIC" }
	end

	configuration "vs*"
		-- Windows and Visual C++ 2005/2008
		defines					{ "_CRT_SECURE_NO_DEPRECATE" }

	configuration "Debug"
		targetsuffix 	"d"
		buildoptions 	{ "-O0" }
		flags 			{ "Symbols" }
		defines			{ "DEBUG", "_DEBUG" }

	configuration "Release"
--		buildoptions 	{ "-fno-strict-aliasing" }
		flags			{ "OptimizeSpeed" }
		defines			{ "NDEBUG" }

