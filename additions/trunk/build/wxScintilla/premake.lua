package.name = "wxScintilla"

package.kind = "dll"
package.language = "c++"
package.files = { matchrecursive( "../../src/wxScintilla/*.cpp" ), matchrecursive( "../../src/wxScintilla/scintilla/*.cxx" ) }

-- Set object output directory.
package.config["Debug"].objdir = ".objsd"
package.config["Debug (Unicode)"].objdir = ".objsud"
package.config["Release"].objdir = ".objs"
package.config["Release (Unicode)"].objdir = ".objsu"

-- Set the targets.
if ( OS == "windows") then
	if ( target == "cb-gcc" or target == "gnu" ) then
		package.config["Debug"].target = "wxmsw270md_scintilla_gcc"
		package.config["Debug (Unicode)"].target = "wxmsw270umd_scintilla_gcc"
		package.config["Release"].target = "wxmsw270m_scintilla_gcc"
		package.config["Release (Unicode)"].target = "wxmsw270um_scintilla_gcc"
	else
		package.config["Debug"].target = "wxmsw270md_scintilla_vc"
		package.config["Debug (Unicode)"].target = "wxmsw270umd_scintilla_vc"
		package.config["Release"].target = "wxmsw270m_scintilla_vc"
		package.config["Release (Unicode)"].target = "wxmsw270um_scintilla_vc"
	end
else
	package.config["Debug"].target = "`wx-config --debug --basename`_scintilla-`wx-config --release`"
	package.config["Release"].target = "`wx-config --basename`_scintilla-`wx-config --release`"
end

-- Set the build options for the Unicode build Targets.
package.buildflags = { "extra-warnings" }
package.config["Debug (Unicode)"].buildflags = { "unicode" }
package.config["Release"].buildflags = { "no-symbols", "optimize-speed" }
package.config["Release (Unicode)"].buildflags = { "unicode", "no-symbols", "optimize-speed" }

-- Set include paths
package.includepaths = { "../../include", "$(WXWIN)/include", "../../src/wxScintilla", "../../src/wxScintilla/scintilla/include", "../../src/wxScintilla/scintilla/src" }

-- Setup the linker options.
if ( target == "cb-gcc" or target == "gnu" ) then
	package.libpaths = { "$(WXWIN)/lib/gcc_dll" }
else
	package.libpaths = { "$(WXWIN)/lib/vc_dll" }
end

-- Setup the output directory options.
if ( target == "cb-gcc" or target == "gnu" ) then
	package.bindir = ".../../lib/gcc_dll"
	package.libdir = "../../lib/gcc_lib"
else
	package.bindir = "../../lib/vc_dll"
	package.libdir = "../../lib/vc_lib"
end

-- Set libraries to link.
if ( OS == "windows") then
	package.links = { "Gdi32" }
	package.config["Debug"].links = { "wxmsw27d" }
	package.config["Debug (Unicode)"].links = { "wxmsw27ud" }
	package.config["Release"].links = { "wxmsw27" }
	package.config["Release (Unicode)"].links = { "wxmsw27u" }
else
	package.config["Debug"].linkoptions = { "`wx-config --debug --libs`"}
	package.config["Release"].linkoptions = { "`wx-config --libs`" }
end

-- Set defines.
if ( OS == "windows") then
	package.config["Debug"].defines = { "WXMAKINGDLL_SCI", "MONOLITHIC", "LINK_LEXERS", "SCI_LEXER", "DEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "__WXDEBUG__", "WXUSINGDLL" }
	package.config["Debug (Unicode)"].defines = { "WXMAKINGDLL_SCI", "MONOLITHIC", "LINK_LEXERS", "SCI_LEXER", "DEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "__WXDEBUG__", "UNICODE", "_UNICODE", "WXUSINGDLL" }
	package.config["Release"].defines = { "WXMAKINGDLL_SCI", "MONOLITHIC", "LINK_LEXERS", "SCI_LEXER", "NDEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "TIXML_USE_TICPP", "WXUSINGDLL" }
	package.config["Release (Unicode)"].defines = { "WXMAKINGDLL_SCI", "MONOLITHIC", "LINK_LEXERS", "SCI_LEXER", "NDEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "UNICODE", "_UNICODE", "WXUSINGDLL" }
else
	package.config["Debug"].defines = { "WXMAKINGDLL_SCI", "MONOLITHIC", "LINK_LEXERS", "SCI_LEXER", "GTK", "DEBUG", "__WX__", "__WXDEBUG__", "WXUSINGDLL" }
	package.config["Release"].defines = { "WXMAKINGDLL_SCI", "MONOLITHIC", "LINK_LEXERS", "SCI_LEXER", "GTK", "NDEBUG", "__WX__", "WXUSINGDLL" }
end

-- Set build options for Linux.
if ( OS == "linux" ) then
	package.config["Debug"].buildoptions = { "`wx-config --debug=yes --cflags`" }
	package.config["Release"].buildoptions = { "`wx-config --debug=no --cflags`" }
end

