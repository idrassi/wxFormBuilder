-- A solution contains projects, and defines the available configurations

solution "wxFormBuilder"

	language "C++"
	configurations { "Release", "Debug" }
	location ( "../../build/" .. _ACTION )

	local scriptDir = os.getcwd()
	local buildDir 	= solution().location

	os.chdir( buildDir )

	configuration "Debug"
		defines { "DEBUG", "_DEBUG" }
		flags { "ExtraWarnings", "Symbols", "Unicode" }
 
	configuration "Release"
		defines { "NDEBUG" }
		flags { "ExtraWarnings", "OptimizeSpeed", "Unicode" }

	dofile( scriptDir .. "/project.lua" )
	dofile( scriptDir .. "/tinyxml.lua" )
	dofile( scriptDir .. "/plugin_interface.lua" )
--
-- Create dynamically Plugins projects
--
	local plugins = { "additional", "common", "containers", "layout" }
	for _, pluginName in ipairs( plugins ) do
		local plugin 		= pluginName .. "-components-plugin"
		local prj 			= project( plugin )
		local srcDir 		= "../../plugins/" .. pluginName .. "/*.cpp"
		local includeDir 	= "../../plugins/" .. pluginName .. "/*.h"
		local targetDir

		if os.get() == "windows" then
			targetDir = "../../output/plugins/" .. pluginName
			defines		{ "WIN32", "_WINDOWS" }
		else
			targetDir = "../../output/lib/wxformbuilder"
		end

		language 	"C++"
		kind 		"SharedLib"
		objdir		= buildDir
		targetdir 	( targetDir )
		targetname 	( pluginName )
		files 		{ srcDir, includeDir }
		includedirs { "../../sdk/tinyxml", "../../sdk/plugin_interface" }
		libdirs 	{ targetDir, "../../sdk/lib" }
		defines		{ "__WX__", "WXUSINGDLL", "BUILD_DLL", "TIXML_USE_TICPP", "UNICODE", "_UNICODE" }

		configuration "Debug"

			targetsuffix 	"d"
			buildoptions 	{ "-O0", "`$(29xDebug)/wx-config --debug=yes --cflags`" }
			linkoptions		{ "`$(29xDebug)/wx-config --debug=yes --libs all`" }
			defines 		{ "__WXDEBUG__", "__WXFB_DEBUG__" }
			links 			{ "fbPluginInterfaced", "ticppd" }

		configuration "Release"

			buildoptions 	{ "-fno-strict-aliasing", "`$(29xRelease)/wx-config --debug=no --cflags`" }
			linkoptions		{ "`$(29xRelease)/wx-config --debug=no --libs all`" }
			links 			{ "fbPluginInterface", "ticpp" }
	end

--	local prjs = solution().projects
--	for i, prj in ipairs(prjs) do
--		print(prj.name)
--	end

-- Pre-build file creation steps
function CreateShareReadme( filename )
	local text = 
	"This directory and the symlink it contains were created automatically by premake\n" ..
	"to facilitate execution of wxFormBuilder prior to installation on Unix platforms.\n" ..
	"On Unix, wxFormBuilder expects to be executed from a directory named \"output\",\n" ..
	"which is next to a directory named \"share\". The \"share\" directory should have a\n" ..
	"subdirectory named \"wxformbuilder\", which contains the configuration files."

	if ( not os.isfile( filename )  ) then
		local fo = io.open( filename, "w" )
		fo:write( text )
		fo:close()
	end
end

function CreateSymlink( pathToLink, symLink )
	os.execute( "ln -s -f -n " .. pathToLink .. " " .. symLink  )
end

if ( not os.is("windows") ) then
	newoption {
		trigger 	= "skip-symlink",
		description = "Do not create the symlink output/share/wxformbuilder"
	}
	if ( not _OPTIONS["skip-symlink"] ) then
		print( "Running pre-build file creation steps..." )
		-- Create a 'share' directory.
		-- HACK: make sure the warning isn't shown on the console.
		os.execute( "mkdir ../../output/share >/dev/null 2>/dev/null" )
		CreateShareReadme( "../../output/share/README.txt" )
		CreateSymlink( "../../output", "../../output/share/wxformbuilder" )
	end
end

if ( os.is("linux") ) then
	newoption {
		trigger 	= "install",
		description = "Copy the application to the specified path"
	}
	function doinstall(cmd, arg)
		if ( not arg ) then
			error("You must specify an install location")
		end

		os.execute( "../../install/linux/wxfb_export.sh " .. arg )
	end
end

