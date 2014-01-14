-- ----------------------------------------------------------------------------
--	Name:		wxpresents4.lua, a Premake4 script
--	Author:		Ben Cleveland, based on wxpresents.lua by Ryan Pusztai
--	Date:		11/24/2010
--	Version:	1.00
--
--	Notes:
-- ----------------------------------------------------------------------------

-- Package options
newoption
{
	trigger = "wx-shared",
	description = "Link against wxWidgets as a shared library"
}

newoption
{
	trigger = "wx-version",
	description = "Version of the wx library to use (e.g. 28 or 30)"
}

newoption
{
	trigger = "wx-root",
	description = "Specify the wxWidgets build path, useful for wxWidgets builds not installed in your system (alternate/custom builds)"
}

newoption
{
	trigger = "compiler-version",
	description = "Specify the version of the compiler which is used to link to other libraries"
}

newoption
{
	trigger = "monolithic",
	description = "Link against the monolithic build"
}

newoption
{
	trigger = "targetdir-base",
	description = "Base target directory. Defaults to ../../"
}

-- Namespace
wx = {}

local wxVer = _OPTIONS["wx-version"] or "30"
local compilerVersion = _OPTIONS["compiler-version"] or ""
if ActionUsesMSVC() and 30 <= tonumber( wxVer ) then
	if _ACTION == "vs2005" then
		compilerVersion = "80"
	elseif _ACTION == "vs2008" then
		compilerVersion = "90"
	elseif _ACTION == "vs2010" then
		compilerVersion = "100"
	elseif _ACTION == "vs2012" then
		compilerVersion = "110"
	elseif _ACTION == "vs2013" then
		compilerVersion = "120"
	else
		error( "Unsupported version of Visual Studio" )
	end
end

local toolchain = iif( ActionUsesGCC(), "gcc", "vc" ) .. compilerVersion

if os.is("windows") then
	if _OPTIONS["wx-root"] and "" ~= _OPTIONS["wx-root"] then
		wx.root = _OPTIONS["wx-root"]
	else
		wx.root = os.getenv( "WXWIN" )
	end
	
	if not wx.root then
		error( "missing the WXWIN environment variable" )
	end

	if not io.open( wx.root .. "/include/wx/wx.h" ) then
		error( "can't find include/wx/wx.h! - check the value of WXWIN (" .. wx.root .. ")" )
	end

	presets.VerifyDllVersion( wx.root, "/lib/vc" .. compilerVersion .. "_dll/wxbase" .. wxVer .. "u_net_vc" .. compilerVersion .. ".dll", "WXWIN" )
end

---	Configure a C/C++ package to use wxWidgets
--	wx.Configure( package, shouldSetTarget = true, wxVer = "28" )
function wx.Configure( shouldSetTarget )
	local unicodeSuffix = iif( _OPTIONS["unicode"], "u", "" )
	local targetDirBase = _OPTIONS["targetdir-base"] or "../../"
	-- Set the default values.
	if shouldSetTarget == nil then shouldSetTarget = true end
	local targetName = project().name

	-- Set the defines.
	if _OPTIONS["unicode"] then
		defines { "wxUSE_UNICODE" }
	end
	defines "__WX__"

	configuration "Debug"
		defines { "__WXDEBUG__" }
	configuration( {} )

	if _OPTIONS["wx-shared"] then
		defines { "WXUSINGDLL" }
	end

	if ActionUsesMSVC() then
		defines { "wxUSE_NO_MANIFEST=1" }
	end

	local kindVal = presets.GetCustomValue( "kind" ) or ""

	if os.is( "windows" ) then
		if ActionUsesGCC() then
			includedirs { wx.root .. "/include" } -- Needed for the resource complier.
		end

		AddSystemPath( wx.root .. "/include" )

		local linktype = iif( _OPTIONS["wx-shared"], "dll", "lib" )
		local rootPrefix = iif( _ACTION == "codeblocks", "$(#WX.lib)", wx.root .. "/lib" )
		
		local libDir = rootPrefix .. "/" .. toolchain .. "_" .. linktype
		local libDir64 = rootPrefix .. "/" .. toolchain .. "_x64_" .. linktype
		if ActionUsesGCC() then
			libDir64 = rootPrefix .. "/" .. toolchain .. "_" .. linktype .. "_x64"
		end
		local setupHincludeDir = libDir .. "/msw" .. unicodeSuffix
		local setupHincludeDir64 = libDir64 .. "/msw" .. unicodeSuffix
		local targetDir = targetDirBase .. "lib/gcc_dll"
				
		configuration { "Debug", "not x64" }
			AddSystemPath( setupHincludeDir .. "d" )

		configuration { "Release", "not x64" }
			AddSystemPath( setupHincludeDir )

		configuration { "Debug", "x64" }
			AddSystemPath( setupHincludeDir64 .. "d" )

		configuration { "Release", "x64" }
			AddSystemPath( setupHincludeDir64 )

		configuration { "not x64" }
			libdirs { libDir }

		configuration { "x64" }
			libdirs { libDir64 }

		-- Set wxWidgets libraries to link. The order we insert matters for the linker.
		local wxLibs = { "wxmsw" .. wxVer .. unicodeSuffix } --, "wxexpat", "wxjpeg", "wxpng", "wxregex" .. unicodeSuffix, "wxtiff", "wxzlib" }

		configuration { "Debug", "not StaticLib" }
			for _, lib in ipairs( wxLibs ) do
				links { lib .. "d" }
			end

		configuration { "Release", "not StaticLib" }
			for _, lib in ipairs( wxLibs ) do
				links { lib }
			end

		configuration { "not StaticLib" }
			local winLibs =
			{
				"kernel32", "user32", "gdi32"
				--[["wsock32", "comctl32", "psapi", "ws2_32", "opengl32",
				"ole32", "winmm", "oleaut32", "odbc32", "advapi32",
				"oleaut32", "uuid", "rpcrt4", "gdi32", "comdlg32",
				"winspool", "shell32", "kernel32"]]
			}

			if ActionUsesMSVC() then
				table.insert( winLibs, { "gdiplus" } )
			end

			for _, lib in ipairs( winLibs) do
				links { lib }
			end

		configuration( {} )

		-- Set the Windows defines.
		defines { "__WXMSW__" }
		-- Set the targets.
		if shouldSetTarget and not ( kindVal == "WindowedApp" or kindVal == "ConsoleApp" ) then
			configuration	{ "Debug", "StaticLib" }
			   targetname	( wx.LibName( targetName, true, false ) )
			   
			configuration	{ "Debug", "SharedLib" }
			   implibname	( wx.LibName( targetName, true, false ) )
			   targetname	( wx.LibName( targetName, true, true ) )

			configuration	{ "Release", "StaticLib" }
			   targetname 	( wx.LibName( targetName, false, false ) )
			 
			configuration	{ "Release", "SharedLib" }
			   implibname	( wx.LibName( targetName, false, false ) )
			   targetname 	( wx.LibName( targetName, false, true ) )
			   
			configuration	{ "x64" }
				targetdir	( targetDirBase .. "lib/" .. toolchain .. "_x64_" .. linktype )
			 
			configuration	{ "not x64" }
				targetdir	( targetDirBase .. "lib/" .. toolchain .. "_" .. linktype )

		end
		configuration( {} )
	else -- not windows

		excludes "**.rc"

		-- Set wxWidgets Debug build/link options.
		configuration { "Debug" }
			buildoptions { "`wx-config --debug=yes --cflags`" }
			linkoptions { "`wx-config --debug=yes --libs std, gl`" }

		-- Set the wxWidgets Release build/link options.
		configuration { "Release" }
			buildoptions { "`wx-config --debug=no --cflags`" }
			linkoptions { "`wx-config --libs std, gl`" }

		-- Set the Linux defines.
		configuration( {} )
		defines "__WXGTK__"

		-- Set the targets.
		if shouldSetTarget then
			if not ( kindVal == "WindowedApp" or kindVal == "ConsoleApp" ) then
				configuration 	{ "Debug" }
					targetname 	( wx.LibName( targetName, true ) )	--"`wx-config --debug=yes --basename`_"..targetName.."-`wx-config --release`"
					targetdir	( targetDirBase .. "lib" )
					linkoptions ( "-Wl,-soname,lib" .. wx.LibName( targetName, true ) .. ".so" )
				
				configuration 	{ "Release" }
					targetname 	( wx.LibName( targetName ) )	--"`wx-config --basename`_"..targetName.."-`wx-config --release`"
					targetdir	( targetDirBase .. "lib" )
					linkoptions ( "-Wl,-soname,lib" .. wx.LibName( targetName ) .. ".so" )
			end
		end
	end

	configuration( {} )
end

function wx.LibName( targetName, isDebug, sharedLibrary )
	local name = ""
	local unicodeSuffix = iif( _OPTIONS["unicode"], "u", "" )
	-- Make the parameters optional.
	local debug = ""
	if isDebug then debug = "d" end

	if "windows" == os.get() then
		local monolithic = ""
		local vc8 = ""

		if _OPTIONS["monolithic"] then monolithic = "m" end		
		local toolchainSuffix = ""
		if sharedLibrary then
			toolchainSuffix = "_" .. toolchain
		end
		name = "wxmsw" .. wxVer .. unicodeSuffix .. monolithic .. debug .. "_" .. targetName .. toolchainSuffix
		
	elseif "linux" == os.get() then
		local wx_ver = wxVer:sub( 1, 1 ).."."..wxVer:sub( 2 )
		name = "wx_gtk2" .. unicodeSuffix .. debug .. "_" .. targetName:lower() .. "-" .. wx_ver
		--print( name )
	else
		local debug = "no"
		if isDebug then debug = "yes" end
		name = "`wx-config --debug=" .. debug .. " --basename`_" .. targetName .. "-`wx-config --release`"
	end

	return name
end




