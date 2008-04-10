-- ----------------------------------------------------------------------------
--	Author:		RJP Computing <rjpcomputing@gmail.com>
--	Date:		02/04/2007
--	Version:	1.00-beta
--	
--	NOTES:
--		- use the '/' slash for all paths.
--		- call ConfigureWxWidgets() after your project is setup, not before.
-- ----------------------------------------------------------------------------

function trim (s)
    return (string.gsub(s, "^%s*(.-)%s*$", "%1"))
end

-- Package options
addoption( "unicode", "Use the Unicode character set" )
addoption( "with-wx-shared", "Link against wxWidgets as a shared library" )

if ( not windows ) then
	addoption( "disable-wx-debug", "Compile against a wxWidgets library without debugging" )
end

-- Configure a C/C++ package to use wxWidgets
function ConfigureWxWidgets( package, altTargetName, wxVer, wxVerMinor, wxCustom )
	-- Check to make sure that the package is valid.
	assert( type( package ) == "table" )
		
	-- Common setup
	package.language = "c++"

	-- Set the default values.
	local targetName = altTargetName or ""
	local wx_ver = wxVer or "28"
	local wx_ver_minor = wxVerMinor or "0"
	local wx_custom = wxCustom or ""
	
	-- Set object output directory.
	if ( options["unicode"] ) then
		package.config["Debug"].objdir = ".objsud"
		package.config["Release"].objdir = ".objsu"
	else
		package.config["Debug"].objdir = ".objsd"
		package.config["Release"].objdir = ".objs"
	end

	-- Set debug flags
	if ( options["disable-wx-debug"] and ( not windows ) ) then
		debug_option = "--debug=no"
		debug_macro = { "NDEBUG" }
	else
		debug_option = "--debug=yes"
		debug_macro = { "DEBUG", "_DEBUG" }
	end

	-- Set the default targetName if none is specified.
	-- NOTE: Not needed for wxWidgets, just for convienance.
	if ( string.len( targetName ) == 0 ) then
		targetName = package.name
	end

	-- Set the build options.
	package.buildflags = { "extra-warnings" }
	package.config["Release"].buildflags = { "no-symbols", "optimize-speed" }
	if ( options["unicode"] ) then
		table.insert( package.buildflags, "unicode" )
	end
	if ( target == "cb-gcc" or target == "gnu" ) then
		table.insert( package.config["Debug"].buildoptions, "-O0" )
		table.insert( package.config["Release"].buildoptions, "-fno-strict-aliasing" )
	end

	-- Set the defines.
	if ( options["with-wx-shared"] ) then
		table.insert( package.defines, "WXUSINGDLL" )
	end
	if ( options["unicode"] ) then
		table.insert( package.defines, { "UNICODE", "_UNICODE" } )
	end
	
	table.insert( package.defines, "__WX__" )
	table.insert( package.config["Debug"].defines, debug_macro )
	table.insert( package.config["Release"].defines, { "NDEBUG" } )

	if ( OS == "windows" ) then
		-- ******* WINDOWS SETUP ***********
		-- *	Settings that are Windows specific.
		-- *********************************
		
		-- Set wxWidgets include paths 
		if ( target == "cb-gcc" ) then
			table.insert( package.includepaths, { "$(#WX.include)" } )
		else
			table.insert( package.includepaths, { "$(WXWIN)/include" } )
		end
		
		-- Set the correct 'setup.h' include path.
		if ( options["with-wx-shared"] ) then
			if ( options["unicode"] ) then
				if ( target == "cb-gcc" ) then
					table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_dll/mswud" )
					table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_dll/mswu" )
				elseif ( target == "gnu" ) then
					table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_dll/mswud" )
					table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_dll/mswu" )
				else
					table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_dll/mswud" )
					table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_dll/mswu" )
				end
			else
				if ( target == "cb-gcc" ) then
					table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_dll/mswd" )
					table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_dll/msw" )
				elseif ( target == "gnu" ) then
					table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_dll/mswd" )
					table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_dll/msw" )
				else
					table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_dll/mswd" )
					table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_dll/msw" )
				end
			end
		else
			if ( options["unicode"] ) then
				if ( target == "cb-gcc" ) then
					table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_lib/mswud" )
					table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_lib/mswu" )
				elseif ( target == "gnu" ) then
					table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_lib/mswud" )
					table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_lib/mswu" )
				else
					table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_lib/mswud" )
					table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_lib/mswu" )
				end
			else
				if ( target == "cb-gcc" ) then
					table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_lib/mswd" )
					table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_lib/msw" )
				elseif ( target == "gnu" ) then
					table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_lib/mswd" )
					table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_lib/msw" )
				else
					table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_lib/mswd" )
					table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_lib/msw" )
				end
			end
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
		
		-- Set the targets.
		if ( package.kind == "winexe" or package.kind == "exe" ) then
			package.config["Release"].target = targetName
			package.config["Debug"].target = targetName.."d"
		else
			if ( target == "cb-gcc" or target == "gnu" ) then
				if ( options["unicode"] ) then
					package.config["Debug"].target = "wxmsw"..wx_ver..wx_ver_minor.."umd_"..targetName.."_gcc"..wx_custom
					package.config["Release"].target = "wxmsw"..wx_ver..wx_ver_minor.."um_"..targetName.."_gcc"..wx_custom
				else
					package.config["Debug"].target = "wxmsw"..wx_ver..wx_ver_minor.."md_"..targetName.."_gcc"..wx_custom
					package.config["Release"].target = "wxmsw"..wx_ver..wx_ver_minor.."m_"..targetName.."_gcc"..wx_custom
				end
			else
				if ( options["unicode"] ) then
					package.config["Debug"].target = "wxmsw"..wx_ver..wx_ver_minor.."umd_"..targetName.."_vc"..wx_custom
					package.config["Release"].target = "wxmsw"..wx_ver..wx_ver_minor.."um_"..targetName.."_vc"..wx_custom
				else
					package.config["Debug"].target = "wxmsw"..wx_ver..wx_ver_minor.."md_"..targetName.."_vc"..wx_custom
					package.config["Release"].target = "wxmsw"..wx_ver..wx_ver_minor.."m_"..targetName.."_vc"..wx_custom
				end
			end
		end
	else
	-- ******* LINUX SETUP *************
	-- *	Settings that are Linux specific.
	-- *********************************
		-- Ignore resource files in Linux.
		table.insert( package.excludes, matchrecursive( "*.rc" ) )
		
		-- Set wxWidgets build options.
		table.insert( package.config["Debug"].buildoptions, "`wx-config "..debug_option.." --cflags`" )
		table.insert( package.config["Release"].buildoptions, "`wx-config --debug=no --cflags`" )
		
		-- Set the wxWidgets link options.
		table.insert( package.config["Debug"].linkoptions, "`wx-config "..debug_option.." --libs`" )
		table.insert( package.config["Release"].linkoptions, "`wx-config --debug=no --libs`" )
		
		-- Set the targets.
		if ( package.kind == "winexe" or package.kind == "exe" ) then
			package.config["Release"].target = targetName
			package.config["Debug"].target = targetName.."d"
		else
			-- Get wxWidgets lib names
			local wxconfig = io.popen("wx-config " .. debug_option .. " --basename")
			local debugBasename = trim( wxconfig:read("*a") )
			wxconfig:close()
			
			wxconfig = io.popen("wx-config --debug=no --basename")
			local basename = trim( wxconfig:read("*a") )
			wxconfig:close()
			
			wxconfig = io.popen("wx-config --release")
			local release = trim( wxconfig:read("*a") )
			wxconfig:close()
	
			package.config["Debug"].target = debugBasename .. "_" .. targetName .. "-" .. release .. wx_custom
			package.config["Release"].target = basename .. "_" .. targetName .. "-" .. release .. wx_custom
		end
	end
end
	
