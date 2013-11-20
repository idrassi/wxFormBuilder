--*****************************************************************************
--*	Author:		Chris Steenwyk <csteenwyk@gmail.com>
--*	Date:		11/13/2013
--*	Version:	1.00
--*
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- GENERAL SETUP -------------------------------------------------------------
--
project( "scintilla" )
if _OPTIONS[ "shared-libraries" ] then
	kind	"SharedLib"
	defines	{ "MONOLITHIC", "WXMAKINGDLL_SCI", "LINK_LEXERS", "SCI_LEXER" }
else
	kind	"StaticLib"
end

function CommonSetup()
	defines			{}
	if os.is( "linux" ) then
		defines { "GTK" }
	end
	includedirs		{ 
						 "../../include" ,
						"../../src/wxScintilla", 
						"../../src/wxScintilla/scintilla/include", 
						"../../src/wxScintilla/scintilla/src" 
					}
	files			{ 
						"../../src/wxScintilla/*.c*", 
						"../../src/wxScintilla/scintilla/src/*.c*", 
						"../../src/wxScintilla/scintilla/include/*.c*", 
						"../../include/wx/wxScintilla/*.h",
						
						--"../../src/wxScintilla/*.cpp",
						--"../../src/wxScintilla/*.c",
						--"../../src/wxScintilla/scintilla/src/*.cpp",
						--"../../src/wxScintilla/scintilla/src/*.c",
						--"../../src/wxScintilla/scintilla/include/*.cpp",
						--"../../src/wxScintilla/scintilla/include/*.c",
						--"../../include/wx/wxScintilla/*.h",
					}
	Configure()
end

CommonSetup()
wx.Configure( true )
