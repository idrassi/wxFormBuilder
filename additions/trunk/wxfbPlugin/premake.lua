--*****************************************************************************
--*	Author:		RJP Computing <rjpcomputing@gmail.com>
--*	Date:		12/15/2006
--*	Version:	1.00-beta
--*	
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- Create the project
project.name = "wxAdditions Plugin"

-- wxWidgets version
local wx_ver = "28"
local wx_ver_minor = ""

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
package.links = { "TiCPP", "Plugin Interface" }
if ( OS == "windows" ) then
	if ( options["unicode"] ) then
		package.config["Debug"].links =
		{
			"wxmsw"..wx_ver..wx_ver_minor.."umd_plotctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."umd_things_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."umd_awx_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."umd_propgrid_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."umd_scintilla_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."umd_flatnotebook_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."umd_ledbargraph_gcc"
		}
		package.config["Release"].links =
		{
			"wxmsw"..wx_ver..wx_ver_minor.."um_plotctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."um_things_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."um_awx_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."um_propgrid_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."um_scintilla_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."um_flatnotebook_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."um_ledbargraph_gcc"
		}
	else
		package.config["Debug"].links =
		{
			"wxmsw"..wx_ver..wx_ver_minor.."md_plotctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."md_things_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."md_awx_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."md_propgrid_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."md_scintilla_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."md_flatnotebook_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."md_ledbargraph_gcc"
		}
		package.config["Release"].links =
		{
			"wxmsw"..wx_ver..wx_ver_minor.."m_plotctrl_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."m_things_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."m_awx_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."m_propgrid_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."m_scintilla_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."m_flatnotebook_gcc",
			"wxmsw"..wx_ver..wx_ver_minor.."m_ledbargraph_gcc"
		}
	end
else
	if ( options["unicode"] ) then
		package.config["Debug"].links =
		{
			"`wx-config --debug=yes --unicode=yes --basename`_plotctrl-`wx-config --release`",
			"`wx-config --debug=yes --unicode=yes --basename`_things-`wx-config --release`",
			"`wx-config --debug=yes --unicode=yes --basename`_awx-`wx-config --release`",
			"`wx-config --debug=yes --unicode=yes --basename`_propgrid-`wx-config --release`",
			"`wx-config --debug=yes --unicode=yes --basename`_scintilla-`wx-config --release`",
			"`wx-config --debug=yes --unicode=yes --basename`_flatnotebook-`wx-config --release`",
			"`wx-config --debug=yes --unicode=yes --basename`_ledbargraph-`wx-config --release`"
		}
		package.config["Release"].links =
		{
			"`wx-config --debug=no --unicode=yes --basename`_plotctrl-`wx-config --release`",
			"`wx-config --debug=no --unicode=yes --basename`_things-`wx-config --release`",
			"`wx-config --debug=no --unicode=yes --basename`_awx-`wx-config --release`",
			"`wx-config --debug=no --unicode=yes --basename`_propgrid-`wx-config --release`",
			"`wx-config --debug=no --unicode=yes --basename`_scintilla-`wx-config --release`",
			"`wx-config --debug=no --unicode=yes --basename`_flatnotebook-`wx-config --release`",
			"`wx-config --debug=no --unicode=yes --basename`_ledbargraph-`wx-config --release`"
		}
	else
		package.config["Debug"].links =
		{
			"`wx-config --debug=yes --unicode=no --basename`_plotctrl-`wx-config --release`",
			"`wx-config --debug=yes --unicode=no --basename`_things-`wx-config --release`",
			"`wx-config --debug=yes --unicode=no --basename`_awx-`wx-config --release`",
			"`wx-config --debug=yes --unicode=no --basename`_propgrid-`wx-config --release`",
			"`wx-config --debug=yes --unicode=no --basename`_scintilla-`wx-config --release`",
			"`wx-config --debug=yes --unicode=no --basename`_flatnotebook-`wx-config --release`",
			"`wx-config --debug=yes --unicode=no --basename`_ledbargraph-`wx-config --release`"
		}
		package.config["Release"].links =
		{
			"`wx-config --debug=no --unicode=no --basename`_plotctrl-`wx-config --release`",
			"`wx-config --debug=no --unicode=no --basename`_things-`wx-config --release`",
			"`wx-config --debug=no --unicode=no --basename`_awx-`wx-config --release`",
			"`wx-config --debug=no --unicode=no --basename`_propgrid-`wx-config --release`",
			"`wx-config --debug=no --unicode=no --basename`_scintilla-`wx-config --release`",
			"`wx-config --debug=no --unicode=no --basename`_flatnotebook-`wx-config --release`",
			"`wx-config --debug=no --unicode=no --basename`_ledbargraph-`wx-config --release`"
		}
	end
end

-- Set the linker include paths
if ( OS == "windows" ) then
	package.libpaths = { "../lib/gcc_dll" }
else
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
table.insert( package.config["Debug"].defines, { "DEBUG", "_DEBUG", "__WXDEBUG__" } )
table.insert( package.config["Release"].defines, "NDEBUG" )

if ( OS == "windows" ) then
--******* WINDOWS SETUP ***********
--*	Settings that are Windows specific.
--*********************************
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
		elseif ( target == "gnu" ) then
			table.insert( package.libpaths, "$(WXWIN)/lib/gcc_dll" )
		else
			table.insert( package.libpaths, "$(WXWIN)/lib/vc_dll" )
		end
	else
		if ( target == "cb-gcc" ) then
			table.insert( package.libpaths, "$(#WX.lib)/gcc_lib" )
		elseif ( target == "gnu" ) then
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
--******* LINUX SETUP *************
--*	Settings that are Linux specific.
--*********************************
	-- Ignore resource files in Linux.
	table.insert( package.excludes, matchrecursive( "*.rc" ) )
	
	-- Set wxWidgets build options.
	table.insert( package.config["Debug"].buildoptions, "`wx-config --debug=yes --cflags` `pkg-config gtk+-2.0 --cflags`" )
	table.insert( package.config["Release"].buildoptions, "`wx-config --debug=no --cflags` `pkg-config gtk+-2.0 --cflags`" )
	
	-- Set the wxWidgets link options.
	table.insert( package.config["Debug"].linkoptions, "`wx-config --debug --libs`" )
	table.insert( package.config["Release"].linkoptions, "`wx-config --libs`" )
	
	-- Set the Linux defines.
	table.insert( package.defines, "__WXGTK__" )
end

-- Add sdk projects here. (This needs to match the directory name not the package name.)
dopackage( "sdk/plugin_interface" )
dopackage( "sdk/tinyxml" )
