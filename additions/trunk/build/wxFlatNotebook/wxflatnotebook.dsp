# Microsoft Developer Studio Project File - Name="wxflatnotebook" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=flatnotebook - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wxflatnotebook.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wxflatnotebook.mak" CFG="flatnotebook - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "flatnotebook - Win32 DLL Universal Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "flatnotebook - Win32 DLL Universal Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "flatnotebook - Win32 DLL Universal Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "flatnotebook - Win32 DLL Universal Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "flatnotebook - Win32 DLL Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "flatnotebook - Win32 DLL Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "flatnotebook - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "flatnotebook - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "flatnotebook - Win32 Universal Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "flatnotebook - Win32 Universal Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "flatnotebook - Win32 Universal Release" (based on "Win32 (x86) Static Library")
!MESSAGE "flatnotebook - Win32 Universal Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "flatnotebook - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "flatnotebook - Win32 Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "flatnotebook - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "flatnotebook - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "flatnotebook - Win32 DLL Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivudll\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivudll\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswunivu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270u_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswunivu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270u_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivu" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270u_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
# ADD RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivu" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270u_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270u_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27u_flatnotebook.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270u_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27u_flatnotebook.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivuddll\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivuddll\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270ud_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270ud_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivud" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270ud_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivud" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270ud_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270ud_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27ud_flatnotebook.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270ud_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27ud_flatnotebook.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivdll\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivdll\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswuniv" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswuniv" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i ".\lib\vc_dll\mswuniv" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
# ADD RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i ".\lib\vc_dll\mswuniv" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27_flatnotebook.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27_flatnotebook.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivddll\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivddll\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270d_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270d_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswunivd" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270d_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswunivd" /i "..\..\..\include" /d WXDLLNAME=wxmswuniv270d_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270d_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27d_flatnotebook.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270d_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27d_flatnotebook.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswudll\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswudll\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270u_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270u_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "_UNICODE" /i ".\lib\vc_dll\mswu" /i "..\..\..\include" /d WXDLLNAME=wxmsw270u_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
# ADD RSC /l 0x409 /d "__WXMSW__" /d "_UNICODE" /i ".\lib\vc_dll\mswu" /i "..\..\..\include" /d WXDLLNAME=wxmsw270u_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270u_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27u_flatnotebook.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270u_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27u_flatnotebook.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswuddll\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswuddll\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270ud_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270ud_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswud" /i "..\..\..\include" /d WXDLLNAME=wxmsw270ud_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswud" /i "..\..\..\include" /d WXDLLNAME=wxmsw270ud_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270ud_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27ud_flatnotebook.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270ud_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27ud_flatnotebook.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswdll\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswdll\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\msw" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\msw" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /i ".\lib\vc_dll\msw" /i "..\..\..\include" /d WXDLLNAME=wxmsw270_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
# ADD RSC /l 0x409 /d "__WXMSW__" /i ".\lib\vc_dll\msw" /i "..\..\..\include" /d WXDLLNAME=wxmsw270_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27_flatnotebook.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27_flatnotebook.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswddll\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswddll\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270d_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270d_flatnotebook_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_FNB" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswd" /i "..\..\..\include" /d WXDLLNAME=wxmsw270d_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswd" /i "..\..\..\include" /d WXDLLNAME=wxmsw270d_flatnotebook_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_FNB
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270d_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27d_flatnotebook.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270d_flatnotebook_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27d_flatnotebook.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivu\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivu\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswunivu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27u_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswunivu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27u_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27u_flatnotebook.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27u_flatnotebook.lib"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivud\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivud\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27ud_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27ud_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27ud_flatnotebook.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27ud_flatnotebook.lib"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswuniv\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswuniv\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswuniv" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswuniv" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27_flatnotebook.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27_flatnotebook.lib"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivd\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivd\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27d_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27d_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27d_flatnotebook.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27d_flatnotebook.lib"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswu\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswu\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27u_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "_UNICODE" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswu" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27u_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "_UNICODE" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27u_flatnotebook.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27u_flatnotebook.lib"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswud\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswud\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27ud_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswud" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27ud_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27ud_flatnotebook.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27ud_flatnotebook.lib"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_msw\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_msw\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\msw" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\msw" /I "..\..\..\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27_flatnotebook.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27_flatnotebook.lib"

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswd\flatnotebook"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswd\flatnotebook"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27d_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswd" /I "..\..\..\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27d_flatnotebook.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27d_flatnotebook.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27d_flatnotebook.lib"

!ENDIF

# Begin Target

# Name "flatnotebook - Win32 DLL Universal Unicode Release"
# Name "flatnotebook - Win32 DLL Universal Unicode Debug"
# Name "flatnotebook - Win32 DLL Universal Release"
# Name "flatnotebook - Win32 DLL Universal Debug"
# Name "flatnotebook - Win32 DLL Unicode Release"
# Name "flatnotebook - Win32 DLL Unicode Debug"
# Name "flatnotebook - Win32 DLL Release"
# Name "flatnotebook - Win32 DLL Debug"
# Name "flatnotebook - Win32 Universal Unicode Release"
# Name "flatnotebook - Win32 Universal Unicode Debug"
# Name "flatnotebook - Win32 Universal Release"
# Name "flatnotebook - Win32 Universal Debug"
# Name "flatnotebook - Win32 Unicode Release"
# Name "flatnotebook - Win32 Unicode Debug"
# Name "flatnotebook - Win32 Release"
# Name "flatnotebook - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\.\..\..\src\wxFlatNotebook\fnb_resources.cpp
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxFlatNotebook\popup_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxFlatNotebook\renderer.cpp
# End Source File
# Begin Source File

SOURCE=.\..\..\..\src\msw\version.rc

!IF  "$(CFG)" == "flatnotebook - Win32 DLL Universal Unicode Release"


!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Universal Unicode Debug"


!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Universal Release"


!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Universal Debug"


!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Unicode Release"


!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Unicode Debug"


!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Release"


!ELSEIF  "$(CFG)" == "flatnotebook - Win32 DLL Debug"


!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Universal Unicode Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Universal Unicode Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Universal Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Universal Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Unicode Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Unicode Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "flatnotebook - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\wxFlatNotebook\wxFlatNotebook.cpp
# End Source File
# End Group
# End Target
# End Project

