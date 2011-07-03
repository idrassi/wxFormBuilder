project "wxFormBuilder"

	kind        		"WindowedApp"
	language			"C++"
	linkoptions 		{ "-mwindows" }

	if os.get() == "windows" then
		defines 		{ "WIN32", "_WINDOWS" }
		libdirs 		{ "../../output" }
		targetdir 		"../../output"
	elseif os.get() == "macosx" then
		excludes 		{ "**.rc" }
		libdirs 		{ "../../output/lib/wxformbuilder" }
		linkoptions 	{ "-L../../output/lib/wxformbuilder" }
		targetdir 		"../../output/bin"
		targetname 		"wxformbuilder"
	else
		excludes 		{ "**.rc" }
		libdirs 		{ "../../output/lib/wxformbuilder" }
		targetdir 		"../../output/bin"
		targetname 		"wxformbuilder"

		local temp = "-Wl,-rpath,"
		if _ACTION == "codelite" then
			temp = temp .. "$$``ORIGIN/../lib/wxformbuilder"
		elseif _ACTION == "codeblocks" then
			temp = temp .. "$``ORIGIN/../lib/wxformbuilder"
		end
		linkoptions 	{ temp }
	end

	defines				{ "NO_GCC_PRAGMA", "SCI_NAMESPACE", "TIXML_USE_TICPP", "UNICODE", "_UNICODE", "__WX__", "WXUSINGDLL", "WXUSINGDLL_FNB" }
	includedirs 		{ "../../src", "../../src/boost", "../../src/controls/include", "../../sdk/tinyxml", "../../sdk/plugin_interface" }
	files				{ "../../src/**.h", "../../src/**.hh", "../../src/**.hpp", "../../src/**.cc", "../../src/**.cpp" }
    excludes            { "../../src/controls/include/wx/propgrid/**", "../../src/controls/src/propgrid/**",
                          "../../src/controls/include/wx/wxScintilla/**", "../../src/controls/src/wxScintilla/**",
                          "../../src/rad/inspector/objinspect.h", "../../src/rad/inspector/objinspect.cpp" }
	flags 				{ "ExtraWarnings", "Unicode" }
	libdirs 			{ "../../sdk/lib", "../../output/lib/wxformbuilder" }
	links 				{ "fbPluginInterface", "ticpp" }
	objdir = 			scriptDir

	configuration "vs*"
		-- Windows and Visual C++ 2005/2008
		defines			{ "_CRT_SECURE_NO_DEPRECATE" }

	configuration "Debug"
		targetsuffix 	"d"
		buildoptions	{ "-O0", "`$(29xDebug)/wx-config --debug=yes --cflags`" }
		linkoptions		{ "`$(29xDebug)/wx-config --debug=yes --libs all`" }
		flags 			{ "Symbols" }
		defines			{ "DEBUG", "_DEBUG", "__WXDEBUG__", "__WXFB_DEBUG__" }

	configuration "Release"
		buildoptions 	{ "-fno-strict-aliasing", "`$(29xRelease)/wx-config --debug=no --cflags`" }
		linkoptions		{ "`$(29xRelease)/wx-config --debug=no --libs all`" }
		flags			{ "OptimizeSpeed" }
		defines			{ "NDEBUG" }

