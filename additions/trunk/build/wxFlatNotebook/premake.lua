package.name = "wxFlatNotebook"

package.kind = "dll"
package.language = "c++"
package.files = { matchfiles( "*.h", "*.cpp" ) }

-- Set object output directory.
package.config["Debug"].objdir = ".objsd"
package.config["Debug (Unicode)"].objdir = ".objsud"
package.config["Release"].objdir = ".objs"
package.config["Release (Unicode)"].objdir = ".objsu"

-- Set the targets.
if ( TARGET == "cb-gcc" or TARGET == "gnu" ) then
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

-- Set the build options for the Unicode build Targets.
package.buildflags = { "extra-warnings" }
package.config["Debug (Unicode)"].buildflags = { "unicode" }
package.config["Release"].buildflags = { "no-symbols", "optimize-speed" }
package.config["Release (Unicode)"].buildflags = { "unicode", "no-symbols", "optimize-speed" }

-- Set include paths
package.includepaths = { "../../include", "$(WXWIN)/include", "../tinyxml" }

-- Setup the linker options.
if ( TARGET == "cb-gcc" or TARGET == "gnu" ) then
	package.libpaths = { "$(WXWIN)/lib/gcc_dll" }
else
	package.libpaths = { "$(WXWIN)/lib/vc_dll" }
end

-- Setup the output directory options.
if ( TARGET == "cb-gcc" or TARGET == "gnu" ) then
	package.bindir = { "../lib/gcc_dll" }
else
	package.bindir = { "../lib/vc_dll" }
end

package.config["Debug"].links = { "wxmsw27d" }
package.config["Debug (Unicode)"].links = { "wxmsw27ud" }
package.config["Release"].links = { "wxmsw27" }
package.config["Release (Unicode)"].links = { "wxmsw27u" }

-- Set defines.
if ( OS == "windows") then
	package.config["Debug"].defines = { "DEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "__WXDEBUG__", "TIXML_USE_TICPP", "WXUSINGDLL" }
	package.config["Debug (Unicode)"].defines = { "DEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "__WXDEBUG__", "TIXML_USE_TICPP", "UNICODE", "_UNICODE", "WXUSINGDLL" }
	package.config["Release"].defines = { "NDEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "TIXML_USE_TICPP", "WXUSINGDLL" }
	package.config["Release (Unicode)"].defines = { "NDEBUG", "WIN32", "_WINDOWS", "HAVE_W32API_H", "__WX__", "__WXMSW__", "TIXML_USE_TICPP", "UNICODE", "_UNICODE", "WXUSINGDLL" }
else
	package.config["Debug"].defines = { "DEBUG", "__WX__", "__WXDEBUG__", "TIXML_USE_TICPP", "WXUSINGDLL" }
	package.config["Release"].defines = { "NDEBUG", "__WX__", "TIXML_USE_TICPP", "WXUSINGDLL" }
end

-- Set build optionsfor Linux.
if ( OS == "linux" ) then
	package.config["Debug"].buildoptions = { "`wx-config --debug=yes --cflags`" }
	package.config["Release"].buildoptions = { "`wx-config --debug=no --cflags`" }
end

