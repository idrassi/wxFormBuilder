-- ----------------------------------------------------------------------------
--	Author:		Ryan Pusztai <csteenwyk@gmail.com>
--	Date:		11/13/2013
--	Version:	1.00
--
--	Copyright (C) 2013 Chris Steenwyk
--
--	Permission is hereby granted, free of charge, to any person obtaining a copy
--	of this software and associated documentation files (the "Software"), to deal
--	in the Software without restriction, including without limitation the rights
--	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
--	copies of the Software, and to permit persons to whom the Software is
--	furnished to do so, subject to the following conditions:
--
--	The above copyright notice and this permission notice shall be included in
--	all copies or substantial portions of the Software.
--
--	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
--	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
--	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
--	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
--	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
--	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
--	THE SOFTWARE.
--
--	NOTES:
--		- use the '/' slash for all paths.
--		- call Configure() after your project is setup, not before.
-- ----------------------------------------------------------------------------

presets = {}

newoption
{
   trigger     = "dynamic-runtime",
   description = "Use the dynamically loadable version of the runtime."
}

newoption
{
   trigger     = "unicode",
   description = "Use the Unicode character set."
}

newoption
{
   trigger     = "force-32bit",
   description = "Forces GCC to build as a 32bit only"
}

newoption
{
   trigger     = "no-extra-warnings",
   description = "Do not enable extra warnings."
}

newoption
{
   trigger     = "shared-libraries",
   description = "Build shared libraries."
}

if os.is("windows") then
	newoption
	{
	   trigger     = "disable-mingw-mthreads",
	   description = "Disables the MinGW specific -mthreads compile option."
	}
end

if os.is("linux") then
	newoption
	{
		trigger		= "rpath",
		description	= "Linux only, set rpath on the linker line to find shared libraries next to executable"
	}

	newoption
	{
		trigger		= "soname",
		description	= "Linux only, set soname on the linker line"
	}
end

presets.cpp11Option = "c++11"
newoption
{
    trigger = presets.cpp11Option,
    description = "Enable C++11 compliler support where available"
}

-- use the "platform" option to specify a platform, instead of add a platform
presets.platform = _OPTIONS["platform"]
_OPTIONS["platform"] = nil -- premake 4.4 beta 4 rejects the option when "Native" is not in solution().platforms

-- the version of the windows API for the _WIN32_WINNT macro, and others like it
presets.WindowsAPIVersion = "0x0501"

---	Change an option to be enabled by default.
--	@param name The name of the option to enable
--  @note Pass "no" to disable the option. Example @code --dynamic-runtime no @endcode
function EnableOption( name )
	if ( _OPTIONS[name] == "no" ) then
		_OPTIONS[name] = nil
	else
		_OPTIONS[name] = ""
	end
end

---	Explicitly disable an option
--	@param name The name of the option to disable
function DisableOption( name )
	_OPTIONS[name] = nil
end

if _OPTIONS["shared-libraries"] then
	EnableOption( "dynamic-runtime" )
end

---	Configures a target with  a set of this pre-configuration.
--	@param pkg Premake 'package' passed in that gets all the settings manipulated.
--
--	Options supported:
--		dynamic-runtime - "Use the dynamicly loadable version of the runtime."
--		unicode - "Use the Unicode character set."
--		disable-mingw-mthreads - "Disables the MinGW specific -mthreads compile option."
--
--	Required package setup:
--		package.name
--		package.includepaths	(if needed)
--		package.links			(if needed)
--	Default package setup: (if not specifically set)
--		package.language					= "c++"
--		package.kind						= "exe" (make this "winexe" if you don't want a console)
--		package.target						= package.name
--		package.config["Debug"].target		= package.name.."d"
--		package.files						= matchrecursive( "*.cpp", "*.h" )
--		package.libpaths					= { "libs" }
--	Appended to package setup:
--		package.buildflags (where appropriate)	= { "extra-warnings", "static-runtime", "no-symbols", "optimize", "no-main", "unicode" }
--											  (VC) { "seh-exceptions", "no-64bit-checks" }
--		package.buildoptions				= (GCC) { "-W", "-Wno-unknown-pragmas", "-Wno-deprecated", "-fno-strict-aliasing"[, "-mthreads"] }
--		package.linkoptions					= (GCC/Windows) { ["-mthreads"] }
--											  (Linux) { ["-fPIC"] }
--		package.defines						= { ["UNICODE", "_UNICODE"] }
--											  (Windows) { "_WIN32", "WIN32", "_WINDOWS" }
--											  (VC) { "_CRT_SECURE_NO_DEPRECATE" }
--		package.config["Debug"].defines		= { "DEBUG", "_DEBUG" }
--		package.config["Release"].defines	= { "NDEBUG" }
--		package.files						= (Windows) matchfiles( "*.rc" )
--		package.links						= (Windows) { "psapi", "ws2_32", "version" }
--											  (Linux) { "pthread", "dl", "m" }
--	Set and can not be changed:
--		pkg.objdir							= ".obj[u]"
--
--	Console Example:
--		dofile( "build/presets.lua" )
--		package.name = "MyCoolApplication"
--		...
--		-- It will include all *.cpp and *.h files in all sub-directories,
--		-- so no need to specify.
--		-- Make this application a console app.
--		Configure( package )
--
--	Static Library Example:
--		dofile( "build/presets.lua" )
--		package.name = "MyCoolStaticLibrary"
--		package.kind = "lib"
--		...
--		-- It will include all *.cpp and *.h files in all sub-directories,
--		-- so no need to specify.
--		-- Make this application a console app.
--		Configure( package )
--
--	Dll Example:
--		dofile( "build/presets.lua" )
--		package.name = "MyCoolDll"
--		package.kind = "dll"
--		...
--		-- It will include all *.cpp and *.h files in all sub-directories,
--		-- so no need to specify.
--		-- Make this application a console app.
--		Configure( package )
--
--	GUI Example:
--		dofile( "build/presets.lua" )
--		package.name = "MyCoolGUIApplication"
--		package.kind = "winexe"
--		...
--		-- It will include all *.cpp and *.h files in all sub-directories,
--		-- so no need to specify.
--		-- Make this application a GUI app.
--		Configure( package )
function presets.GetCustomValue( item )
	local prj = project()
	for _, block in pairs( prj.blocks ) do
		if block[item] then
			return block[item]
		end
	end
	return nil
end

function Configure()

	if presets.platform then
		solution().platforms = { presets.platform }
	end

	cfg = configuration()

	if not project() then
		error( "There is no currently active project. Please use the project() method to create a project first." )
	end

	configuration( {} )

	if not language() then
		language "C++"
	end

	local kindVal = presets.GetCustomValue( "kind" )
	if kindVal then
		if "WindowedApp" == kindVal then
			flags( "WinMain" )
		elseif "StaticLib" == kindVal then
			if not presets.GetCustomValue( "targetdir" ) then
				targetdir( solution().basedir .. "/lib" )
			end
		end
	else
		kind( "ConsoleApp" )
	end

	if not presets.GetCustomValue( "objdir" ) then
		objdir( ".obj/" .. iif( _ACTION, _ACTION, "" ) )
	end

	if (not _OPTIONS["no-extra-warnings"]) or (_OPTIONS["no-extra-warnings"] == "no") then
		flags( "ExtraWarnings" )
		if ActionUsesGCC() then
			buildoptions( "-W" )
		end
	end

    if _OPTIONS[ presets.cpp11Option ] and ActionUsesGCC() then
        buildoptions  { "-std=c++11" }
    end

	-- targetdir, implibdir, and libdirs defaults --------------------------------------
	configuration "x32 or native"
		if nil == SolutionTargetDir( false ) then
			if "StaticLib" == kindVal then
				targetdir( solution().basedir .. "/lib" )
			else
				targetdir( solution().basedir .. "/bin" )
			end
		end
		if nil == next( SolutionLibDirs( false ) ) then
			libdirs( { solution().basedir .. "/lib", solution().basedir .. "/bin" } )
		end
		--[[ TODO: When the build agents are upgraded to premake 4.4, enable this line. Until then, we rely on the fact that
				our linux build agents all use 64-bit linux.
		]]
		if os.is( "windows" ) then --or ( os.is( "linux" ) and not os.is64bit() ) then
			if ActionUsesGCC() then
				buildoptions( "-m32" )
				linkoptions( "-m32" )
				resoptions( "-F pe-i386" )
			end
		end

	-- 64 bit compatibility -------------------------------------------------------------------
	configuration "x64"
		if nil == SolutionTargetDir( false ) then
			if "StaticLib" == kindVal then
				targetdir( solution().basedir .. "/lib64" )
			else
				targetdir( solution().basedir .. "/bin64" )
			end
		end
		if nil == next( SolutionLibDirs( false ) ) then
			libdirs( { solution().basedir .. "/lib64", solution().basedir .. "/bin64" } )
		end
		if os.get() == "windows" then
			defines( { "_WIN64" } )
		end
		if ActionUsesMSVC() then
			buildoptions( "/bigobj" )
		end
		if ActionUsesGCC() then
			buildoptions( "-m64" )
			linkoptions( "-m64" )
		end

	configuration( "not dynamic-runtime" )
		flags( "StaticRuntime" )

	configuration( "Debug" )
		if not presets.GetCustomValue( "targetsuffix" ) then
			targetsuffix( "d" )
		end
		defines( { "DEBUG", "_DEBUG" } )
		flags( "Symbols" )

	configuration( "Release" )
		defines( { "NDEBUG" } )
		flags( "Optimize" )

	configuration( "unicode" )
		flags( "Unicode" )
		defines( { "UNICODE", "_UNICODE" } )
		objdir( ".obju/" .. iif( _ACTION, _ACTION, "" ) )

	-- COMPILER SPECIFIC SETUP ----------------------------------------------------
	--
	configuration( "gmake or codelite or codeblocks or xcode3" )
		buildoptions( { "-Wno-unknown-pragmas", "-Wno-deprecated", "-fno-strict-aliasing" } )
		if os.get() == "windows" then
			linkoptions( { "-Wl,--enable-auto-import" } )
			flags( "NoImportLib" )
			if not _OPTIONS["disable-mingw-mthreads"] then
				buildoptions( "-mthreads" )
				linkoptions( "-mthreads" )
			end
		end

		-- Force gcc to build a 32bit target.
		if _OPTIONS["force-32bit"] then
			buildoptions( "-m32" )
			linkoptions( "-m32" )
		end

	configuration( "vs*" )
		flags( { "SEH", "No64BitChecks" } )
		defines( { "_CRT_SECURE_NO_DEPRECATE", "_SCL_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_DEPRECATE" } )
		buildoptions
		{
			"/we 4150",
			"/wd 4503" -- disable warning: "decorated name length exceeded, name was truncated"
		}

	configuration( "vs2008 or vs2010 or vs2012" )
		-- multi-process building
		flags( "NoMinimalRebuild" )
		buildoptions( "/MP" )

	-- OPERATING SYSTEM SPECIFIC SETTINGS -----------------------------------------
	--
	configuration( "windows" )
		-- Maybe add "*.manifest" later, but it seems to get in the way.
		files( "*.rc" )
		defines( { "_WIN32", "WIN32", "_WINDOWS", "NOMINMAX", "_WIN32_WINNT=" .. presets.WindowsAPIVersion, "WINVER=" .. presets.WindowsAPIVersion } )

	configuration( { "windows", "not StaticLib" } )
		links( { "psapi", "ws2_32", "version", "winmm" } )

	configuration( { "linux", "not StaticLib" } )
		links( { "pthread", "dl", "m", "rt" } )

	configuration( { "linux", "StaticLib" } )
		-- lib is only needed because Premake automatically adds the -fPIC to dlls
		buildoptions( "-fPIC" )

	configuration( "linux" )
		-- Set rpath
		local useRpath = true
		local rpath="$$``ORIGIN"
		local rpathOption = _OPTIONS[ "rpath" ]

		if rpathOption then
			if "no" == rpathOption or "" == rpathOption then
				useRpath = false
			else
				rpath = rpathOption
			end
		end

		if useRpath then
			linkoptions( "-Wl,-rpath," .. rpath )
		end

		-- Set soname
		local sonameOption = _OPTIONS[ "soname" ]
		if sonameOption then
			if "no" ~= sonameOption and "" ~= sonameOption then
				linkoptions( "-Wl,-soname," .. sonameOption )
			end
		end

	configuration(cfg.terms)
end

-- Adds path as a system path in gcc so warnings are ignored
function AddSystemPath( path )
	if type(path) ~= "string" then
		error( "AddSystemPath only accepts a string", 2 )
	end
	if ("codelite" == _ACTION) or ("codeblocks" == _ACTION) or ("xcode3" == _ACTION) then
		buildoptions( "-isystem " .. path )
	elseif ("gmake" == _ACTION) then
		buildoptions( "-isystem \"" .. path .. "\"" )
	else
		includedirs( path )
	end
end

function SolutionTargetDir( setError )
	setError = setError or false
	local sln = solution()
	if ( sln.blocks[1] and sln.blocks[1].targetdir ) then
		return solution().blocks[1].targetdir
	end

	if setError then
		error( "targetdir has not been set on the solution", 2 )
	end
end

function SolutionImpLibDir( setError )
	setError = setError or false
	local sln = solution()
	if ( sln.blocks[1] and sln.blocks[1].implibdir ) then
		return solution().blocks[1].implibdir
	end

	if setError then
		error( "implibdir has not been set on the solution", 2 )
	end
end

function SolutionLibDirs( setError )
	setError = setError or false
	local sln = solution()
	if ( sln.blocks[1] and sln.blocks[1].libdirs ) then
		return solution().blocks[1].libdirs
	end

	if setError then
		error( "libdirs has not been set on the solution", 2 )
	end
end

function ActionUsesGCC()
	return ("gmake" == _ACTION or "codelite" == _ACTION or "codeblocks" == _ACTION or "xcode3" == _ACTION)
end

function ActionUsesMSVC()
	return (_ACTION and _ACTION:find("vs"))
end

function presets.CopyFile( sourcePath, destinationDirectory )
	sourceFile = string.gsub( sourcePath, "([\\]+)", "/" )
	local unquotedSource = string.gsub( sourceFile, '"', '' )

	destinationDirectory = string.gsub( destinationDirectory, "([\\]+)", "/" )
	local unquotedDestination = string.gsub( destinationDirectory, '"', '' )

	if not os.isdir( unquotedDestination ) then
		print( "Creating Directory: " .. unquotedDestination ); io.stdout:flush()
		local created, msg = os.mkdir( unquotedDestination )
		if( not created ) then
			error( "presets.CopyFile Failed: " .. msg, 2 )
		end
	end

	local sourceFileName = path.getname( unquotedSource )
	if sourceFileName ~= path.getname( unquotedDestination ) then
		unquotedDestination = unquotedDestination .. "/" .. sourceFileName
	end

	if not os.isfile( unquotedSource ) then
		print( "Could not find file: " .. unquotedSource )
	end

	print( "os.copyfile( " .. unquotedSource .. ", " .. unquotedDestination .. " )" ); io.stdout:flush()

	local copied, msg = os.copyfile( unquotedSource, unquotedDestination )
	if not copied then
		error( "presets.CopyFile Failed: " .. msg, 2 )
	end
end

---
-- return true if platform will be included in the generated solution
--
function presets.SolutionHasPlatform( platform )
	return (platform == presets.platform) or (solution().platforms and table.contains( solution().platforms, platform ))
end

-- hack to make the visual studio version selector work with vs2012 express
function VS2012ExpressHeader(sln)
	_p('Microsoft Visual Studio Solution File, Format Version 12.00')
	_p('# Visual Studio Express 2012 for Windows Desktop')
end

if (_ACTION == "vs2012")  and os.isfile( os.getenv("VS110COMNTOOLS") .. "..\\IDE\\WDExpress.exe" ) then
	premake.vstudio.sln2005.header = VS2012ExpressHeader
end


function presets.VerifyDllVersion( envPath, relPathToDLL, strName )

--check for the right version of VS libs
	-- the libs don't have any truly identifying info, but the dlls do.
	-- call dumpbin -headers on that dll, and parse out linker version
	if _ACTION:find( "vs" ) then
		local dllPath = envPath .. relPathToDLL
		local dumpBinPath = "../../VC/bin/dumpbin.exe"
		local vscomntools = ""
		local expectedVersion = "0"
		if _ACTION == "vs2005" then
			vscomntools = os.getenv( "VS80COMNTOOLS" )
			expectedVersion = "8.00"
		elseif _ACTION == "vs2008" then
			vscomntools = os.getenv( "VS90COMNTOOLS" )
			expectedVersion = "8.00"	-- Legacy wx workaround
		elseif _ACTION == "vs2010" then
			vscomntools = os.getenv( "VS100COMNTOOLS" )
			expectedVersion = "10.00"
		elseif _ACTION == "vs2012" then
			vscomntools = os.getenv( "VS110COMNTOOLS" )
			expectedVersion = "11.00"
		elseif _ACTION == "vs2013" then
			vscomntools = os.getenv( "VS120COMNTOOLS" )
			expectedVersion = "12.00"
		end

		if vscomntools then
			--this commandline has to execute dumpbin -headers inside an environment setup by vwvars32.bat.
			--the generated path should look something like:
			--cmd.exe /C ""C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools\vsvars32.bat" && "C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools\../../VC/bin/dumpbin.exe" -headers E:\SourceCode\Libraries\wxWidgets2.8.11.03/lib/vc_dll/wxbase28_net_vc.dll"

			local cmdline = "cmd.exe /C \"\"" .. vscomntools .. "vsvars32.bat\" && \"" .. vscomntools .. dumpBinPath .. "\" -headers \"" .. dllPath .. "\" 2>&1\"" 
			local file = assert( io.popen( cmdline ))
			local output = file:read( '*all' )
			file:close()
			local strStart, strEnd, match = string.find( output, "(%d+.%d+)%slinker version" )
			if match == nil then
				print (cmdline)
				print( output )
				print( strStart )
				print( strEnd )
				print( match )
				print ( string.sub( output, strStart, strEnd ) )

				error ("error getting linker version from VS tools:  Cannot verify " .. strName .. " libs" )
			end

			if match ~= expectedVersion then
				error( strName .. " directory does not appear to contain libraries compatible with " .. _ACTION .. ".  " .. "\n linker version: " .. match .. "\n $" .. strName .. ":" .. envPath  )
			end
		else
			print ("unable to find VS tools.  Cannot verify " .. strName .. " libs" )
		end
	end
end
