package.name = "wxFlatNotebook"

package.kind = "dll"
package.language = "c++"
package.files = { matchfiles( "../../src/wxFlatNotebook/*.cpp", "../../include/wx/wxFlatNotebook/*.h" ) }

-- Local variables
local wx_ver = "27"
local wx_ver_minor = "0"

-- Set object output directory.
package.config["Debug"].objdir = ".objsd"
package.config["Debug (Unicode)"].objdir = ".objsud"
package.config["Release"].objdir = ".objs"
package.config["Release (Unicode)"].objdir = ".objsu"

-- Set the targets.
if ( OS == "windows") then
	if ( target == "cb-gcc" or target == "gnu" ) then
		package.config["Debug"].target = "wxmsw"..wx_ver..wx_ver_minor.."md_flatnotebook_gcc"
		package.config["Debug (Unicode)"].target = "wxmsw"..wx_ver..wx_ver_minor.."umd_flatnotebook_gcc"
		package.config["Release"].target = "wxmsw"..wx_ver..wx_ver_minor.."m_flatnotebook_gcc"
		package.config["Release (Unicode)"].target = "wxmsw"..wx_ver..wx_ver_minor.."um_flatnotebook_gcc"
	else
		package.config["Debug"].target = "wxmsw"..wx_ver..wx_ver_minor.."md_flatnotebook_vc"
		package.config["Debug (Unicode)"].target = "wxmsw"..wx_ver..wx_ver_minor.."umd_flatnotebook_vc"
		package.config["Release"].target = "wxmsw"..wx_ver..wx_ver_minor.."m_flatnotebook_vc"
		package.config["Release (Unicode)"].target = "wxmsw"..wx_ver..wx_ver_minor.."um_flatnotebook_vc"
	end
else
	package.config["Debug"].target = "`wx-config --debug --basename`_flatnotebook-`wx-config --release`"
	package.config["Release"].target = "`wx-config --basename`_flatnotebook-`wx-config --release`"
end

-- Set the build options for the Unicode build Targets.
package.buildflags = { "extra-warnings" }
package.config["Debug (Unicode)"].buildflags = { "unicode" }
package.config["Release"].buildflags = { "no-symbols", "optimize-speed" }
package.config["Release (Unicode)"].buildflags = { "unicode", "no-symbols", "optimize-speed" }

-- Set include paths
if ( OS == "windows") then
	if ( target == "cb-gcc" ) then
		package.includepaths = { "../../include", "$(#WX.include)" }
	else
		package.includepaths = { "../../include", "$(WXWIN)/include" }
	end
else
	package.includepaths = { "../../include" }
end

-- Setup the linker options.
if ( target == "cb-gcc" or target == "gnu" ) then
	if ( target == "cb-gcc" and OS == "windows" ) then
		package.libpaths = { "$(#WX.lib)/gcc_dll" }
	else
		package.libpaths = { "$(WXWIN)/lib/gcc_dll" }
	end
else
	package.libpaths = { "$(WXWIN)/lib/vc_dll" }
end

-- Setup the output directory options.
if ( OS == "windows") then
	package.bindir = "../../../../bin"
	package.libdir = "../../../../bin"
else
	package.bindir = "../../../../bin"
	package.libdir = "../../../../bin/lib"
end

-- Set libraries to link.
if ( OS == "windows") then
	package.config["Debug"].links = { "wxmsw"..wx_ver.."d" }
	package.config["Debug (Unicode)"].links = { "wxmsw"..wx_ver.."ud" }
	package.config["Release"].links = {	"wxmsw"..wx_ver }
	package.config["Release (Unicode)"].links = { "wxmsw"..wx_ver.."u" }
else
	package.config["Debug"].linkoptions = { "`wx-config --debug --libs`"}
	package.config["Release"].linkoptions = { "`wx-config --libs`" }
end

-- Set defines.
if ( OS == "windows") then
	package.config["Debug"].defines = { "WXMAKINGDLL_FNB", "MONOLITHIC", "DEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "__WXDEBUG__", "WXUSINGDLL" }
	package.config["Debug (Unicode)"].defines = { "WXMAKINGDLL_FNB", "MONOLITHIC", "DEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "__WXDEBUG__", "UNICODE", "_UNICODE", "WXUSINGDLL" }
	package.config["Release"].defines = { "WXMAKINGDLL_FNB", "MONOLITHIC", "NDEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "TIXML_USE_TICPP", "WXUSINGDLL" }
	package.config["Release (Unicode)"].defines = { "WXMAKINGDLL_FNB", "MONOLITHIC", "NDEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "UNICODE", "_UNICODE", "WXUSINGDLL" }
else
	package.config["Debug"].defines = { "WXMAKINGDLL_FNB", "MONOLITHIC", "DEBUG", "__WX__", "__WXDEBUG__", "WXUSINGDLL" }
	package.config["Release"].defines = { "WXMAKINGDLL_FNB", "MONOLITHIC", "NDEBUG", "__WX__", "WXUSINGDLL" }
end

-- Set build optionsfor Linux.
if ( OS == "linux" ) then
	package.config["Debug"].buildoptions = { "`wx-config --debug=yes --cflags`" }
	package.config["Release"].buildoptions = { "`wx-config --debug=no --cflags`" }
end

