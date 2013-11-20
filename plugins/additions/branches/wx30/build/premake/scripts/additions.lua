-- ----------------------------------------------------------------------------
--	Author:		RJP Computing <rjpcomputing@gmail.com>
--	Date:		02/05/2007
--	Version:	1.00-beta
--	
--	NOTES:
--		- use the '/' slash for all paths.
-- ----------------------------------------------------------------------------
-- Adding additional options to support all the build types.
addoption( "shared", "Create a dynamic link library (.dll) version" )

-- Includes
dofile( "premake/scripts/wxpresets.lua" )

-- Configure a C/C++ package to use wxWidgets
function MakeWxAdditionsPackage( package, altTargetName, wxVer, wxVerMinor, wxCustom )
	-- Check to make sure that the package is valid.
	assert( type( package ) == "table" )
	
	-- Set the default values.
	local targetName = altTargetName or ""
	local wx_ver = wxVer or "28"
	local wx_ver_minor = wxVerMinor or "0"
	local wx_custom = wxCustom or ""
	
	-- Set the kind of package you want to create.
	--		Options: exe | winexe | lib | dll
	if ( options["shared"] ) then
		package.kind = "dll"
	else
		package.kind = "lib"
	end

	-- Setup the package compiler settings.
	package.buildflags = { "static-runtime" }

	if ( target == "vs2005" ) then
		-- Windows and Visual C++ 2005
		package.defines = { "_CRT_SECURE_NO_DEPRECATE" }
	end

	-- Setup the output directory options.	
	if ( windows ) then
		if ( ( target == "gnu" ) or ( target == "cb-gcc" ) or ( target == "cl-gcc" ) ) then
			package.bindir = "../../lib/gcc_dll"
			package.libdir = "../../lib/gcc_lib"
		else
			package.bindir = "../../lib/vc_dll"
			package.libdir = "../../lib/vc_lib"
		end
	else
		package.bindir = "../../lib"
		package.libdir = "../../lib"
		table.insert( package.buildoptions, "-fPIC" )
	end
		
	-- Set the include paths.
	table.insert( package.includepaths, "../../include" )
	
	-- Make this package a wxWidgets package.
	-- NOTE: Call this after your project is setup.
	ConfigureWxWidgets( package, targetName, wx_ver, wx_ver_minor, wx_custom )
	
end
	
