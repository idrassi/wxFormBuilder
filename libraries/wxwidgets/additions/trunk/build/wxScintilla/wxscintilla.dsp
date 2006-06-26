# Microsoft Developer Studio Project File - Name="wxscintilla" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=wxscintilla - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wxscintilla.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wxscintilla.mak" CFG="wxscintilla - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wxscintilla - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "wxscintilla - Win32 DebugUnicode" (based on "Win32 (x86) Static Library")
!MESSAGE "wxscintilla - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "wxscintilla - Win32 ReleaseUnicode" (based on "Win32 (x86) Static Library")
!MESSAGE "wxscintilla - Win32 DLL Debug Monolithic" (based on "Win32 (x86) Static Library")
!MESSAGE "wxscintilla - Win32 DLL Release Monolithic" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wxscintilla - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "$(WXWIN)\additions\lib\vc_lib"
# PROP BASE Intermediate_Dir "$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(WXWIN)\additions\lib\vc_lib"
# PROP Intermediate_Dir "$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /W3 /O2 /Ob1 /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "_CRT_SECURE_NO_DEPRECATE" /GF /Gy /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /GX 
# ADD CPP /nologo /MT /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /W3 /O2 /Ob1 /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "_CRT_SECURE_NO_DEPRECATE" /GF /Gy /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2055 
# ADD RSC /l 2055 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Release\wxscintilla.bsc" 
# ADD BSC32 /nologo /o ".\Release\wxscintilla.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(WXWIN)\additions\lib\vc_lib\wxscintilla.lib" 
# ADD LIB32 /nologo /out:"$(WXWIN)\additions\lib\vc_lib\wxscintilla.lib" 

!ELSEIF  "$(CFG)" == "wxscintilla - Win32 DebugUnicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(WXWIN)\additions\lib\vc_lib"
# PROP BASE Intermediate_Dir "$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "$(WXWIN)\additions\lib\vc_lib"
# PROP Intermediate_Dir "$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /Zi /W4 /Od /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "_CRT_SECURE_NO_DEPRECATE" /D "_UNICODE" /Gm /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /GX 
# ADD CPP /nologo /MTd /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /Zi /W4 /Od /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "_CRT_SECURE_NO_DEPRECATE" /D "_UNICODE" /Gm /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2055 
# ADD RSC /l 2055 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\DebugUnicode\wxscintilla.bsc" 
# ADD BSC32 /nologo /o ".\DebugUnicode\wxscintilla.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(WXWIN)\additions\lib\vc_lib\wxscintillaud.lib" 
# ADD LIB32 /nologo /out:"$(WXWIN)\additions\lib\vc_lib\wxscintillaud.lib" 

!ELSEIF  "$(CFG)" == "wxscintilla - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(WXWIN)\additions\lib\vc_lib"
# PROP BASE Intermediate_Dir "$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "$(WXWIN)\additions\lib\vc_lib"
# PROP Intermediate_Dir "$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /Zi /W4 /Od /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "_CRT_SECURE_NO_DEPRECATE" /Gm /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /GX 
# ADD CPP /nologo /MTd /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /Zi /W4 /Od /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "_CRT_SECURE_NO_DEPRECATE" /Gm /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2055 
# ADD RSC /l 2055 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Debug\wxscintilla.bsc" 
# ADD BSC32 /nologo /o ".\Debug\wxscintilla.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(WXWIN)\additions\lib\vc_lib\wxscintillad.lib" 
# ADD LIB32 /nologo /out:"$(WXWIN)\additions\lib\vc_lib\wxscintillad.lib" 

!ELSEIF  "$(CFG)" == "wxscintilla - Win32 ReleaseUnicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "$(WXWIN)\additions\lib\vc_lib"
# PROP BASE Intermediate_Dir "$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(WXWIN)\additions\lib\vc_lib"
# PROP Intermediate_Dir "$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /W3 /O2 /Ob1 /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "_CRT_SECURE_NO_DEPRECATE" /D "_UNICODE" /GF /Gy /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /GX 
# ADD CPP /nologo /MT /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /W3 /O2 /Ob1 /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "_CRT_SECURE_NO_DEPRECATE" /D "_UNICODE" /GF /Gy /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2055 
# ADD RSC /l 2055 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\ReleaseUnicode\wxscintilla.bsc" 
# ADD BSC32 /nologo /o ".\ReleaseUnicode\wxscintilla.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(WXWIN)\additions\lib\vc_lib\wxscintillau.lib" 
# ADD LIB32 /nologo /out:"$(WXWIN)\additions\lib\vc_lib\wxscintillau.lib" 

!ELSEIF  "$(CFG)" == "wxscintilla - Win32 DLL Debug Monolithic"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(WXWIN)\additions\lib\vc_dll"
# PROP BASE Intermediate_Dir "$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "$(WXWIN)\additions\lib\vc_dll"
# PROP Intermediate_Dir "$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /Zi /W4 /Od /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "WXUSINGDLL" /D "WXMAKINGDLL_SCI" /D "_CRT_SECURE_NO_DEPRECATE" /Gm /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /GX 
# ADD CPP /nologo /MDd /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /Zi /W4 /Od /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "WXUSINGDLL" /D "WXMAKINGDLL_SCI" /D "_CRT_SECURE_NO_DEPRECATE" /Gm /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2055 
# ADD RSC /l 2055 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Debug\wxscintilla.bsc" 
# ADD BSC32 /nologo /o ".\Debug\wxscintilla.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo 
# ADD LIB32 /nologo 

!ELSEIF  "$(CFG)" == "wxscintilla - Win32 DLL Release Monolithic"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "$(WXWIN)\additions\lib\vc_dll"
# PROP BASE Intermediate_Dir "$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(WXWIN)\additions\lib\vc_dll"
# PROP Intermediate_Dir "$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /Zi /W3 /O2 /Ob1 /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "WXUSINGDLL" /D "WXMAKINGDLL_SCI" /D "_CRT_SECURE_NO_DEPRECATE" /GF /Gy /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /GX 
# ADD CPP /nologo /MD /I ""$(WXWIN)\additions\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\include"" /I ""$(WXWIN)\additions\src\wxScintilla\scintilla\src"" /Zi /W3 /O2 /Ob1 /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WX__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "WXUSINGDLL" /D "WXMAKINGDLL_SCI" /D "_CRT_SECURE_NO_DEPRECATE" /GF /Gy /GR /Fp"$(ConfigurationName)/wxscintilla.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2055 
# ADD RSC /l 2055 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Release\wxscintilla.bsc" 
# ADD BSC32 /nologo /o ".\Release\wxscintilla.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo 
# ADD LIB32 /nologo 

!ENDIF

# Begin Target

# Name "wxscintilla - Win32 Release"
# Name "wxscintilla - Win32 DebugUnicode"
# Name "wxscintilla - Win32 Debug"
# Name "wxscintilla - Win32 ReleaseUnicode"
# Name "wxscintilla - Win32 DLL Debug Monolithic"
# Name "wxscintilla - Win32 DLL Release Monolithic"
# Begin Group "wxScintilla"

# PROP Default_Filter ""
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\wxScintilla\PlatWX.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\ScintillaWX.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\wxscintilla.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\wxScintilla\PlatWX.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\ScintillaWX.h
# End Source File
# End Group
# End Group
# Begin Group "Scintilla"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\AutoComplete.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\AutoComplete.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\CallTip.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\CallTip.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\CellBuffer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\CellBuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\ContractionState.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\ContractionState.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\Document.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\Document.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\DocumentAccessor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\DocumentAccessor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\Editor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\Editor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\ExternalLexer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\ExternalLexer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\Indicator.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\Indicator.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\KeyMap.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\KeyMap.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\KeyWords.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexAda.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexAPDL.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexAsm.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexAsn1.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexAU3.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexAVE.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexBaan.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexBash.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexBasic.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexBullant.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexCaml.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexCLW.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexConf.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexCPP.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexCrontab.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexCsound.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexCSS.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexEiffel.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexErlang.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexEScript.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexFlagship.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexForth.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexFortran.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexGui4Cli.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexHaskell.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexHTML.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexKix.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexLisp.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexLout.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexLua.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexMatlab.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexMetapost.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexMMIXAL.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexMPT.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexMSSQL.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexNsis.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexOthers.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexPascal.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexPB.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexPerl.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexPOV.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexPS.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexPython.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexRebol.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexRuby.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexScriptol.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexSmalltalk.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexSpecman.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexSQL.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexTADS3.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexTeX.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexVB.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexVerilog.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexVHDL.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LexYAML.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LineMarker.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\LineMarker.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\PropSet.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\RESearch.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\RESearch.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\ScintillaBase.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\ScintillaBase.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\Style.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\Style.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\StyleContext.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\StyleContext.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\SVector.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\UniConversion.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\UniConversion.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\ViewStyle.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\ViewStyle.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\WindowAccessor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\XPM.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wxScintilla\scintilla\src\XPM.h
# End Source File
# End Group
# End Target
# End Project

