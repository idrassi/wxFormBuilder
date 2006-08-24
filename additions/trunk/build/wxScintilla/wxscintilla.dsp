# Microsoft Developer Studio Project File - Name="wxscintilla" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=scintilla - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wxscintilla.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wxscintilla.mak" CFG="scintilla - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "scintilla - Win32 DLL Universal Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "scintilla - Win32 DLL Universal Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "scintilla - Win32 DLL Universal Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "scintilla - Win32 DLL Universal Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "scintilla - Win32 DLL Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "scintilla - Win32 DLL Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "scintilla - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "scintilla - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "scintilla - Win32 Universal Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla - Win32 Universal Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla - Win32 Universal Release" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla - Win32 Universal Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla - Win32 Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "scintilla - Win32 DLL Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivudll\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivudll\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswunivu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270u_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswunivu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270u_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivu" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270u_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
# ADD RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivu" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270u_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270u_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27u_scintilla.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270u_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27u_scintilla.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivuddll\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivuddll\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270ud_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270ud_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivud" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270ud_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivud" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270ud_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270ud_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27ud_scintilla.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270ud_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27ud_scintilla.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivdll\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivdll\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswuniv" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswuniv" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i ".\lib\vc_dll\mswuniv" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
# ADD RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i ".\lib\vc_dll\mswuniv" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27_scintilla.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27_scintilla.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivddll\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivddll\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270d_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270d_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswunivd" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270d_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswunivd" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270d_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270d_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27d_scintilla.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270d_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27d_scintilla.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswudll\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswudll\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270u_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270u_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "_UNICODE" /i ".\lib\vc_dll\mswu" /i "..\..\..\include" /d WXDLLNAME=wxmsw270u_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
# ADD RSC /l 0x409 /d "__WXMSW__" /d "_UNICODE" /i ".\lib\vc_dll\mswu" /i "..\..\..\include" /d WXDLLNAME=wxmsw270u_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270u_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27u_scintilla.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270u_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27u_scintilla.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswuddll\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswuddll\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270ud_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270ud_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswud" /i "..\..\..\include" /d WXDLLNAME=wxmsw270ud_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswud" /i "..\..\..\include" /d WXDLLNAME=wxmsw270ud_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270ud_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27ud_scintilla.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270ud_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27ud_scintilla.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswdll\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswdll\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\msw" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\msw" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /i ".\lib\vc_dll\msw" /i "..\..\..\include" /d WXDLLNAME=wxmsw270_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
# ADD RSC /l 0x409 /d "__WXMSW__" /i ".\lib\vc_dll\msw" /i "..\..\..\include" /d WXDLLNAME=wxmsw270_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27_scintilla.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27_scintilla.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswddll\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswddll\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270d_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270d_scintilla_vc_custom.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /D "WXMAKINGDLL_SCI" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswd" /i "..\..\..\include" /d WXDLLNAME=wxmsw270d_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswd" /i "..\..\..\include" /d WXDLLNAME=wxmsw270d_scintilla_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d "SCI_LEXER" /d "LINK_LEXERS" /d "__WX__" /d "WXMAKINGDLL_SCI" /i ".\..\..\src\wxScintilla\scintilla\include" /i .\..\..\src\wxScintilla\scintilla\src
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270d_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27d_scintilla.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270d_scintilla_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27d_scintilla.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "scintilla - Win32 Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivu\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivu\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswunivu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27u_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswunivu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27u_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27u_scintilla.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27u_scintilla.lib"

!ELSEIF  "$(CFG)" == "scintilla - Win32 Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivud\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivud\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27ud_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27ud_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27ud_scintilla.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27ud_scintilla.lib"

!ELSEIF  "$(CFG)" == "scintilla - Win32 Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswuniv\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswuniv\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswuniv" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswuniv" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27_scintilla.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27_scintilla.lib"

!ELSEIF  "$(CFG)" == "scintilla - Win32 Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivd\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivd\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27d_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27d_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27d_scintilla.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27d_scintilla.lib"

!ELSEIF  "$(CFG)" == "scintilla - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswu\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswu\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27u_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "_UNICODE" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27u_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "_UNICODE" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27u_scintilla.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27u_scintilla.lib"

!ELSEIF  "$(CFG)" == "scintilla - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswud\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswud\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27ud_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27ud_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27ud_scintilla.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27ud_scintilla.lib"

!ELSEIF  "$(CFG)" == "scintilla - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_msw\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_msw\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\msw" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\msw" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27_scintilla.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27_scintilla.lib"

!ELSEIF  "$(CFG)" == "scintilla - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswd\scintilla"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswd\scintilla"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27d_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27d_scintilla.pdb /I ".\..\..\include" /I ".\..\..\src\wxScintilla\scintilla\include" /I ".\..\..\src\wxScintilla\scintilla\src" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "SCI_LEXER" /D "LINK_LEXERS" /D "__WX__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27d_scintilla.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27d_scintilla.lib"

!ENDIF

# Begin Target

# Name "scintilla - Win32 DLL Universal Unicode Release"
# Name "scintilla - Win32 DLL Universal Unicode Debug"
# Name "scintilla - Win32 DLL Universal Release"
# Name "scintilla - Win32 DLL Universal Debug"
# Name "scintilla - Win32 DLL Unicode Release"
# Name "scintilla - Win32 DLL Unicode Debug"
# Name "scintilla - Win32 DLL Release"
# Name "scintilla - Win32 DLL Debug"
# Name "scintilla - Win32 Universal Unicode Release"
# Name "scintilla - Win32 Universal Unicode Debug"
# Name "scintilla - Win32 Universal Release"
# Name "scintilla - Win32 Universal Debug"
# Name "scintilla - Win32 Unicode Release"
# Name "scintilla - Win32 Unicode Debug"
# Name "scintilla - Win32 Release"
# Name "scintilla - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\AutoComplete.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\CallTip.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\CellBuffer.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\CharClassify.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\ContractionState.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\Document.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\DocumentAccessor.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\Editor.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\ExternalLexer.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\Indicator.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\KeyMap.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\KeyWords.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexAPDL.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexAU3.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexAVE.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexAda.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexAsm.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexAsn1.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexBaan.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexBash.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexBasic.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexBullant.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexCLW.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexCPP.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexCSS.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexCaml.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexConf.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexCrontab.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexCsound.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexEScript.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexEiffel.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexErlang.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexFlagship.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexForth.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexFortran.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexGui4Cli.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexHTML.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexHaskell.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexInno.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexKix.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexLisp.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexLout.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexLua.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexMMIXAL.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexMPT.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexMSSQL.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexMatlab.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexMetapost.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexNsis.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexOpal.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexOthers.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexPB.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexPOV.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexPS.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexPascal.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexPerl.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexPython.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexRebol.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexRuby.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexSQL.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexScriptol.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexSmalltalk.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexSpecman.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexSpice.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexTADS3.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexTCL.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexTeX.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexVB.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexVHDL.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexVerilog.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LexYAML.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\LineMarker.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\PlatWX.cpp
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\PropSet.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\RESearch.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\ScintillaBase.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\ScintillaWX.cpp
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\Style.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\StyleContext.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\UniConversion.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\ViewStyle.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\WindowAccessor.cxx
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\scintilla\src\XPM.cxx
# End Source File
# Begin Source File

SOURCE=.\..\..\..\src\msw\version.rc

!IF  "$(CFG)" == "scintilla - Win32 DLL Universal Unicode Release"


!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Universal Unicode Debug"


!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Universal Release"


!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Universal Debug"


!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Unicode Release"


!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Unicode Debug"


!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Release"


!ELSEIF  "$(CFG)" == "scintilla - Win32 DLL Debug"


!ELSEIF  "$(CFG)" == "scintilla - Win32 Universal Unicode Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "scintilla - Win32 Universal Unicode Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "scintilla - Win32 Universal Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "scintilla - Win32 Universal Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "scintilla - Win32 Unicode Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "scintilla - Win32 Unicode Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "scintilla - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "scintilla - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxScintilla\wxscintilla.cpp
# End Source File
# End Group
# End Target
# End Project

