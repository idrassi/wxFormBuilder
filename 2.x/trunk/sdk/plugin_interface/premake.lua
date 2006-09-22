package.name = "plugin_interface"
package.kind = "lib"
package.language = "c++"
package.files = { matchfiles( "*.h", "*.cpp" ) }
package.libdir = "lib"
package.targetextension = "a"
-- Set object output directory.
package.config["Debug"].objdir = ".objsd"
package.config["DebugUnicode"].objdir = ".objsud"
package.config["Release"].objdir = ".objs"
package.config["ReleaseUnicode"].objdir = ".objsu"
-- Set the targets.
package.config["Debug"].target = "fbPluginInterfaced"
package.config["DebugUnicode"].target = "fbPluginInterfaceud"
package.config["Release"].target = "fbPluginInterface"
package.config["ReleaseUnicode"].target = "fbPluginInterfaceu"
-- Set include paths
package.includepaths = { "$(#WX.include)", "../tinyxml" }
-- Set defines.
package.config["Debug"].defines = 
{
	"DEBUG",
	"WIN32",
	"_WINDOWS",
	"HAVE_W32API_H",
	"__WX__",
	"__WXMSW__",
	"__WXDEBUG__",	
	"TIXML_USE_TICPP"
}
package.config["DebugUnicode"].defines = 
{
	"DEBUG",
	"WIN32",
	"_WINDOWS",
	"HAVE_W32API_H",
	"__WX__",
	"__WXMSW__",
	"__WXDEBUG__",	
	"TIXML_USE_TICPP",
	"UNICODE",
	"_UNICODE",
	"wxUSE_UNICODE"
}
package.config["Release"].defines = 
{
	"NDEBUG",
	"WIN32",
	"_WINDOWS",
	"HAVE_W32API_H",
	"__WX__",
	"__WXMSW__",
	"TIXML_USE_TICPP"
}
package.config["ReleaseUnicode"].defines = 
{
	"NDEBUG",
	"WIN32",
	"_WINDOWS",
	"HAVE_W32API_H",
	"__WX__",
	"__WXMSW__",
	"TIXML_USE_TICPP",
	"UNICODE",
	"_UNICODE",
	"wxUSE_UNICODE"
}
