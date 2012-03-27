--*****************************************************************************
--*	Author:		RJP Computing <rjpcomputing@gmail.com>
--*	Date:		12/15/2006
--*	Version:	1.00-beta
--*	
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- Set debug flags
if ( not windows ) then
	addoption( "disable-wx-debug", "Compile against a wxWidgets library without debugging" )
	
	if ( options["disable-wx-debug"] ) then
		debug_option = "--debug=no"
		debug_macro = { "NDEBUG", "__WXFB_DEBUG__" }
	else
		debug_option = "--debug=yes"
		debug_macro = { "DEBUG", "_DEBUG", "__WXFB_DEBUG__" }
	end
	
	if ( options["unicode"] ) then
		unicode_option = "--unicode=yes"
	else
		unicode_option = "--unicode=no"
	end
end

-- Create the project
project.name = "wxAdditions Plugin"

-- wxWidgets version
local wx_ver = "28"
local wx_ver_minor = ""
local wx_custom = ""

--******* Initial Setup ************
--*	Most of the setting are set here.
--**********************************
package = newpackage()
-- Set the name of your package.
package.name = "wxAdditions_Plugin"
-- Set the targets.
package.config["Debug"].target = "wxadditionsd"
package.config["Release"].target = "wxadditions"
-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "dll"
-- Set the files to include.
package.files = { matchfiles( "*.cpp", "*.h") }
-- Set the include paths.
package.includepaths = { "../include", "sdk/tinyxml", "sdk/plugin_interface" }
-- Set the libraries it links to.
package.links = { "TiCPP", "plugin-interface" }

if ( OS == "windows" ) then
	if ( options["unicode"] ) then
		package.config["Debug"].links =
		{
			"wxmsw"..wx_ver..wx_ver_minor.."umd_plotctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."umd_things_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."umd_treelistctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."umd_awx_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."umd_ledbargraph_gcc"
		}
		package.config["Release"].links =
		{
			"wxmsw"..wx_ver..wx_ver_minor.."um_plotctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."um_things_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."um_treelistctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."um_awx_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."um_ledbargraph_gcc"
		}
	else
		package.config["Debug"].links =
		{
			"wxmsw"..wx_ver..wx_ver_minor.."md_plotctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."md_things_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."md_treelistctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."md_awx_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."md_ledbargraph_gcc"
		}
		package.config["Release"].links =
		{
			"wxmsw"..wx_ver..wx_ver_minor.."m_plotctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."m_things_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."m_treelistctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."m_awx_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."m_ledbargraph_gcc"
		}
	end
	
	-- Set the linker include paths
	package.libpaths = { "../lib/gcc_dll" }
else
	-- Set the linker include paths
	package.libpaths = { "../lib" }
end

-- Load the dlls from the plugin's directory.
if ( OS == "linux" ) then
	if ( target == "cb-gcc" ) then
		table.insert( package.linkoptions, "-Wl,-rpath,$``ORIGIN" )
	else
		table.insert( package.linkoptions, "-Wl,-rpath,$$``ORIGIN" )
	end
end

-- Setup the output directory options.
--		Note: Use 'libdir' for "lib" kind only.
package.bindir = "wxAdditions"
-- Set the defines.
package.defines = { "TIXML_USE_TICPP", "BUILD_DLL" }

-- Hack the dll output to prefix 'lib' to the begining.
package.targetprefix = "lib"

--------------------------- DO NOT EDIT BELOW ----------------------------------

--******* GENAERAL SETUP **********
--*	Settings that are not dependant
--*	on the operating system.
--*********************************
-- Package options
addoption( "unicode", "Use the Unicode character set" )
addoption( "with-wx-shared", "Link against wxWidgets as a shared library" )

-- Common setup
package.language = "c++"

-- Set object output directory.
if ( options["unicode"] ) then
	package.config["Debug"].objdir = ".objsud"
	package.config["Release"].objdir = ".objsu"
else
	package.config["Debug"].objdir = ".objsd"
	package.config["Release"].objdir = ".objs"
end

-- Set the build options.
package.buildflags = { "extra-warnings" }
package.config["Release"].buildflags = { "no-symbols", "optimize-speed" }
if ( options["unicode"] ) then
	table.insert( package.buildflags, "unicode" )
end

-- Set the defines.
if ( options["with-wx-shared"] ) then
	table.insert( package.defines, "WXUSINGDLL" )
end
if ( options["unicode"] ) then
	table.insert( package.defines, { "UNICODE", "_UNICODE" } )
end
table.insert( package.defines, "__WX__" )
table.insert( package.config["Release"].defines, "NDEBUG" )

if ( target == "cb-gcc" or target == "gnu" or target == "cl-gcc" ) then
	table.insert( package.buildflags, "no-import-lib" )
	table.insert( package.config["Release"].buildoptions, "-fno-strict-aliasing" )
end

if ( OS == "windows" ) then
--******* WINDOWS SETUP ***********
--*	Settings that are Windows specific.
--*********************************
	table.insert( package.config["Debug"].defines, { "DEBUG", "_DEBUG", "__WXDEBUG__", "__WXFB_DEBUG__" } )
	
	-- Set wxWidgets include paths 
	if ( target == "cb-gcc" ) then
		table.insert( package.includepaths, "$(#WX.include)" )
	else
		table.insert( package.includepaths, "$(WXWIN)/include" )
	end
	
	-- Set the linker options.
	if ( options["with-wx-shared"] ) then
		if ( target == "cb-gcc" ) then
			table.insert( package.libpaths, "$(#WX.lib)/gcc_dll" )
		elseif ( target == "gnu" or target == "cl-gcc" ) then
			table.insert( package.libpaths, "$(WXWIN)/lib/gcc_dll" )
		else
			table.insert( package.libpaths, "$(WXWIN)/lib/vc_dll" )
		end
	else
		if ( target == "cb-gcc" ) then
			table.insert( package.libpaths, "$(#WX.lib)/gcc_lib" )
		elseif ( target == "gnu" or target == "cl-gcc" ) then
			table.insert( package.libpaths, "$(WXWIN)/lib/gcc_lib" )
		else
			table.insert( package.libpaths, "$(WXWIN)/lib/vc_lib" )
		end
	end
	
	-- Set wxWidgets libraries to link.
	if ( options["unicode"] ) then
		table.insert( package.config["Release"].links, "wxmsw"..wx_ver.."u" )
		table.insert( package.config["Debug"].links, "wxmsw"..wx_ver.."ud" )
	else
		table.insert( package.config["Release"].links, "wxmsw"..wx_ver )
		table.insert( package.config["Debug"].links, "wxmsw"..wx_ver.."d" )
	end
	
	-- Set the Windows defines.
	table.insert( package.defines, { "__WXMSW__", "WIN32", "_WINDOWS" } )
else
--******* NON WINDOWS SETUP *************
--*	Settings that are specific to non-windows platforms
--*********************************
	table.insert( package.config["Debug"].defines, debug_macro )

	-- Ignore resource files in Linux.
	table.insert( package.excludes, matchrecursive( "*.rc" ) )
	
	-- Set wxWidgets build options.
	table.insert( package.config["Debug"].buildoptions, "`wx-config "..debug_option.." --cflags`" )
	table.insert( package.config["Release"].buildoptions, "`wx-config --debug=no --cflags`" )
		
	-- Set the wxWidgets link options.
	table.insert( package.config["Debug"].linkoptions, "`wx-config "..debug_option.." --libs std plotctrl things treelistctrl awx ledbargraph`" )
	table.insert( package.config["Release"].linkoptions, "`wx-config --debug=no --libs std plotctrl things treelistctrl awx ledbargraph`" )
end

-- Add sdk projects here. (This needs to match the directory name not the package name.)
dopackage( "sdk/plugin_interface" )
dopackage( "sdk/tinyxml/ticpp.lua" )
