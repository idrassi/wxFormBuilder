@echo off
::**************************************************************************
:: File:           wxBuild_wxAdditions.bat
:: Version:        1.00
:: Name:           Chris Steenwyk - Generated for use with Premake4
:: Date:           09/03/2009
:: Description:    Build wxAdditions with the MinGW/Visual C++.
::                 
::**************************************************************************
SETLOCAL
set WXBUILD_VERSION=1.00
set WXBUILD_APPNAME=wxBuild_wxAdditions
:: MinGW4-w64 Gcc install location. This must match your systems configuration.
set MINGW4_W64_DIR=C:\GCC\MinGW-w64\4.8.1
set MINGW4_W64_GCC4VER=48

::Configuration Parameters
set PREMAKE=premake\windows\premake4.exe
set WXVER=30
set PLATFORM=x32
set WXROOT=%WXWIN%
set UNICODE=--unicode
set DYNAMIC_LINK=--wx-shared
set SHARED_LIBRARIES=
set ACTION=
set COMPILER_VERSION=
set MONOLITHIC=

:Loop
IF [%1]==[--wx-root]                  GOTO WxRoot
IF [%1]==[--wx-version]               GOTO WxVersion

if %1 == VC100    	    goto SETUP_VC100_BUILD_ENVIRONMENT
if %1 == vc100    	    goto SETUP_VC100_BUILD_ENVIRONMENT
if %1 == VC100_64 	    goto SETUP_VC100_64_BUILD_ENVIRONMENT
if %1 == vc100_64 	    goto SETUP_VC100_64_BUILD_ENVIRONMENT
if %1 == VC120    	    goto SETUP_VC120_BUILD_ENVIRONMENT
if %1 == vc120    	    goto SETUP_VC120_BUILD_ENVIRONMENT
if %1 == VC120_64 	    goto SETUP_VC120_64_BUILD_ENVIRONMENT
if %1 == vc120_64 	    goto SETUP_VC120_64_BUILD_ENVIRONMENT
if %1 == VC140    	    goto SETUP_VC140_BUILD_ENVIRONMENT
if %1 == vc140    	    goto SETUP_VC140_BUILD_ENVIRONMENT
if %1 == VC140_64 	    goto SETUP_VC140_64_BUILD_ENVIRONMENT
if %1 == vc140_64 	    goto SETUP_VC140_64_BUILD_ENVIRONMENT
if %1 == MINGW4_W64	    goto SETUP_MINGW4_W64_BUILD_ENVIRONMENT
if %1 == mingw4_w64     goto SETUP_MINGW4_W64_BUILD_ENVIRONMENT
if %1 == MINGW4_W64_64  goto SETUP_MINGW4_W64_64_BUILD_ENVIRONMENT
if %1 == mingw4_w64_64  goto SETUP_MINGW4_W64_64_BUILD_ENVIRONMENT
goto COMPILER_ERROR

:WxRoot
SET WXROOT=%2
SHIFT
SHIFT
GOTO Loop

:WxVersion
SET WXVER=%2
SHIFT
SHIFT
GOTO Loop

::**************************************************************************
:: Subroutines
::**************************************************************************
:GETREGISTRYVALUE
%3=
FOR /F "usebackq skip=2 tokens=1-3" %%A IN (`REG QUERY %1 /v %2 2^>nul`) DO (
    set _ValueName=%%A
    set _ValueType=%%B
    set %3=%%C
)
exit /b

:GETMSBUILDPATH
set MSBUILDPATH=
if exist "%ProgramFiles%\MSBuild\14.0\bin" set MSBUILDPATH="%ProgramFiles%\MSBuild\14.0\bin\MSBuild.exe"
if exist "%ProgramFiles(x86)%\MSBuild\14.0\bin" set MSBUILDPATH="%ProgramFiles(x86)%\MSBuild\14.0\bin\MSBuild.exe"
IF not (%MSBUILDPATH%) == () exit /b
IF (%MSBUILDPATH%) == () (
	set REGPATH="HKLM\software\wow6432node\microsoft\visualstudio\sxs\vc7"
	CALL :GETREGISTRYVALUE %REGPATH% "FrameworkDir32" MSBUILDPATH
	)	
IF (%MSBUILDPATH%) == () (
	set REGPATH="HKLM\software\microsoft\visualstudio\sxs\vc7"
	CALL :GETREGISTRYVALUE %REGPATH% "FrameworkDir32" MSBUILDPATH
	)
IF %MSBUILDPATH% == [] goto REGISTRY_ERROR
set MSBUILDVER=""
CALL :GETREGISTRYVALUE %REGPATH% "FrameworkVer32" MSBUILDVER
IF %MSBUILDVER% == [] goto REGISTRY_ERROR
set MSBUILDPATH=%MSBUILDPATH%%MSBUILDVER%\MSBuild.exe
exit /b

:PREMAKE
echo %PREMAKE% --wx-version=%WXVER% --platform=%PLATFORM% --wx-root=%WXROOT% %UNICODE% %MONOLITHIC% %DYNAMIC_LINK% %SHARED_LIBRARIES% %COMPILER_VERSION% %ACTION%
%PREMAKE% --wx-version=%WXVER% --platform=%PLATFORM% --wx-root=%WXROOT% %UNICODE% %MONOLITHIC% %DYNAMIC_LINK% %SHARED_LIBRARIES% %COMPILER_VERSION% %ACTION%
echo.
exit /b

:GENERATE_BUILD_CMD_VC
call :GETMSBUILDPATH
set VCPLATFORM=%PLATFORM%
if %VCPLATFORM% == x32 ( set VCPLATFORM=Win32 )
set BUILD_CMD_RELEASE=%MSBUILDPATH% wxAdditions.sln /verbosity:normal /property:Configuration=Release;_IsNativeEnvironment=false;Platform=%VCPLATFORM%
set BUILD_CMD_DEBUG=%MSBUILDPATH% wxAdditions.sln /verbosity:normal /property:Configuration=Debug;_IsNativeEnvironment=false;Platform=%VCPLATFORM%
echo BUILD_CMD_RELEASE = %BUILD_CMD_RELEASE%
exit /b

:GENERATE_BUILD_CMD_MINGW
echo Assuming that MinGW-w64 has been installed to:
echo   %MINGW4_W64_DIR%
echo.
if "%OS%" == "Windows_NT" set PATH=%MINGW4_W64_DIR%\BIN;%PATH%
if "%OS%" == "" set PATH="%MINGW4_W64_DIR%\BIN";"%PATH%"
set CMDSUFFIX=32
IF %PLATFORM% == x64 ( set CMDSUFFIX=64 )
set BUILD_CMD_RELEASE=mingw32-make config=release%CMDSUFFIX%
set BUILD_CMD_DEBUG=mingw32-make config=debug%CMDSUFFIX%
exit /b

::**************************************************************************
:: Compiler Config
::**************************************************************************

:SETUP_VC100_BUILD_ENVIRONMENT
:: Add the VC 2010 includes.
echo Setting environment for Visual C++ 10.0...
echo.
set ACTION=vs2010
set PLATFORM=x32
call :GENERATE_BUILD_CMD_VC
goto START

:SETUP_VC100_64_BUILD_ENVIRONMENT
:: Add the VC 2010 64-bit includes.
echo Setting environment for Visual C++ 10.0 64-bit...
echo.
set ACTION=vs2010
set PLATFORM=x64
call :GENERATE_BUILD_CMD_VC
goto START

:SETUP_VC120_BUILD_ENVIRONMENT
:: Add the VC 2013 includes.
echo Setting environment for Visual C++ 12.0...
echo.
set ACTION=vs2013
set PLATFORM=x32
call :GENERATE_BUILD_CMD_VC
goto START

:SETUP_VC120_64_BUILD_ENVIRONMENT
:: Add the VC 2013 64-bit includes.
echo Setting environment for Visual C++ 12.0 64-bit...
echo.
set ACTION=vs2013
set PLATFORM=x64
call :GENERATE_BUILD_CMD_VC
goto START

:SETUP_VC140_BUILD_ENVIRONMENT
:: Add the VC 2015 includes.
echo Setting environment for Visual C++ 14.0...
echo.
set ACTION=vs2015
set PLATFORM=x32
call :GENERATE_BUILD_CMD_VC
goto START

:SETUP_VC140_64_BUILD_ENVIRONMENT
:: Add the VC 2015 64-bit includes.
echo Setting environment for Visual C++ 14.0 64-bit...
echo.
set ACTION=vs2015
set PLATFORM=x64
call :GENERATE_BUILD_CMD_VC
goto START

:SETUP_MINGW4_W64_BUILD_ENVIRONMENT
echo Setting environment for MinGW4-w64...
set ACTION=gmake
set PLATFORM=x32
set COMPILER_VERSION=--compiler-version=%MINGW4_W64_GCC4VER%
call :GENERATE_BUILD_CMD_MINGW
goto START

:SETUP_MINGW4_W64_64_BUILD_ENVIRONMENT
echo Setting environment for MinGW4-w64 64-bit...
set ACTION=gmake
set PLATFORM=x64
set COMPILER_VERSION=--compiler-version=%MINGW4_W64_GCC4VER%
call :GENERATE_BUILD_CMD_MINGW
goto START

::**************************************************************************
:: Build Steps
::**************************************************************************

:START
echo %WXBUILD_APPNAME% v%WXBUILD_VERSION%
echo.

if %2 == LIB   goto LIB_BUILD_UNICODE
if %2 == lib   goto LIB_BUILD_UNICODE
if %2 == DLL   goto DLL_BUILD_UNICODE
if %2 == dll   goto DLL_BUILD_UNICODE
if %2 == ALL   goto ALL_BUILD
if %2 == all   goto ALL_BUILD
if %2 == NULL  goto SECIFIC_BUILD
if %2 == null  goto SECIFIC_BUILD
goto WRONGPARAM

:SECIFIC_BUILD
echo Specific mode...
echo.
IF (%3) == () goto ERROR
goto %3

:ALL_BUILD
echo Compiling all versions.
echo.
goto LIB_BUILD_UNICODE

:LIB_BUILD_UNICODE
echo Building Unicode Lib's...
echo.
goto LIB_DEBUG_UNICODE

:LIB_DEBUG_UNICODE
echo Compiling lib debug Unicode...
set SHARED_LIBRARIES=
set DYNAMIC_LINK=
set UNICODE=--unicode
set MONOLITHIC=
call :PREMAKE
%BUILD_CMD_DEBUG%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto LIB_RELEASE_UNICODE

:LIB_RELEASE_UNICODE
echo Compiling lib release Unicode...
set SHARED_LIBRARIES=
set DYNAMIC_LINK=
set UNICODE=--unicode
set MONOLITHIC=
call :PREMAKE
%BUILD_CMD_RELEASE%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto LIB_BUILD_MONO_UNICODE

::_____________________________________________________________________________
:LIB_BUILD_MONO_UNICODE
echo Building Monolithic Unicode lib's...
echo.
goto LIB_DEBUG_MONO_UNICODE

:LIB_DEBUG_MONO_UNICODE
echo Compiling lib debug Unicode monolithic...
set SHARED_LIBRARIES=
set DYNAMIC_LINK=
set UNICODE=--unicode
set MONOLITHIC=--monolithic
call :PREMAKE
%BUILD_CMD_DEBUG%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto LIB_RELEASE_MONO_UNICODE

:LIB_RELEASE_MONO_UNICODE
echo Compiling lib release Unicode monolithic...
set SHARED_LIBRARIES=
set DYNAMIC_LINK=
set UNICODE=--unicode
set MONOLITHIC=--monolithic
call :PREMAKE
%BUILD_CMD_RELEASE%

echo.
:: Check for build all
if %2 == all goto DLL_BUILD_UNICODE
if %2 == ALL goto DLL_BUILD_UNICODE
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto END

:DLL_BUILD_UNICODE
echo Building Unicode Dll's...
echo.
goto DLL_DEBUG_UNICODE

:DLL_DEBUG_UNICODE
echo Compiling dll debug Unicode...
set SHARED_LIBRARIES=--shared-libraries
set DYNAMIC_LINK=--wx-shared
set UNICODE=--unicode
set MONOLITHIC=
call :PREMAKE
%BUILD_CMD_DEBUG%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_RELEASE_UNICODE

:DLL_RELEASE_UNICODE
echo Compiling dll release Unicode...
set SHARED_LIBRARIES=--shared-libraries
set DYNAMIC_LINK=--wx-shared
set UNICODE=--unicode
set MONOLITHIC=
call :PREMAKE
%BUILD_CMD_RELEASE%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_BUILD_MONO_UNICODE

:DLL_BUILD_MONO_UNICODE
echo Building Monolithic Unicode Dll's...
echo.
goto DLL_DEBUG_MONO_UNICODE

:DLL_DEBUG_MONO_UNICODE
echo Compiling dll debug Unicode monolithic...
set SHARED_LIBRARIES=--shared-libraries
set DYNAMIC_LINK=--wx-shared
set UNICODE=--unicode
set MONOLITHIC=--monolithic
call :PREMAKE
%BUILD_CMD_DEBUG%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_RELEASE_MONO_UNICODE

:DLL_RELEASE_MONO_UNICODE
echo Compiling dll release Unicode monolithic...
set SHARED_LIBRARIES=--shared-libraries
set DYNAMIC_LINK=--wx-shared
set UNICODE=--unicode
set MONOLITHIC=--monolithic
call :PREMAKE
%BUILD_CMD_RELEASE%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto END

:REGISTRY_ERROR
echo.
echo REGISTRY ERROR OCCURED!
echo Error determining location of MSBuild
goto SHOW_USAGE

:ERROR
echo.
echo ERROR OCCURED!
echo Not enough command line parameters.
goto SHOW_USAGE

:WRONGPARAM
echo.
echo ERROR OCCURED!
echo The command line parameters was %1. This is not an available option.
goto SHOW_USAGE

:COMPILER_ERROR
echo.
echo ERROR OCCURED!
echo Unsupported compiler. %1 is not an available compiler option.
goto SHOW_USAGE

:MOVE_ERROR
echo.
echo ERROR OCCURED!
echo Unsupported compiler users as a parameter to move. (%1)
goto SHOW_USAGE

:SHOW_USAGE
echo.
echo %WXBUILD_APPNAME% v%WXBUILD_VERSION%
echo     Build wxWidgets with the MinGW/Visual C++ Tool chains.
echo.
echo Usage: "wxBuild_wxWidgets.bat <Compiler{MINGW|VCTK|VC71|VC80|VC90}> <BuildTarget{LIB|DLL|ALL|CLEAN|MOVE|NULL}> [Specific Option (See Below)]"
goto SHOW_OPTIONS

:SHOW_OPTIONS
echo.
echo      Compiler Options:
echo           MINGW4_W64    = MinGW-w64 Gcc v4.x.x compiler
echo           MINGW4_W64_64 = MinGW-w64 Gcc v4.x.x compiler 64-bit
echo           VC100         = Visual C++ 10.0
echo           VC100_64      = Visual C++ 10.0 64-bit
echo           VC120         = Visual C++ 12.0
echo           VC120_64      = Visual C++ 12.0 64-bit
echo.
echo      BuildTarget Options:
echo           LIB   = Builds all the static library targets.
echo           DLL   = Builds all the dynamic library targets.
echo           ALL   = Builds all the targets (Recommended).
echo           NULL  = Used so that you can specify a specific target. (See below)
echo.
echo      Specific Options(Used with NULL):
echo           LIB_DEBUG_UNICODE, LIB_RELEASE_UNICODE,
echo           LIB_DEBUG_MONO_UNICODE, LIB_RELEASE_MONO_UNICODE,
echo.
echo           DLL_DEBUG_UNICODE, DLL_RELEASE_UNICODE,
echo           DLL_DEBUG_MONO_UNICODE, DLL_RELEASE_MONO_UNICODE
echo.
echo      Options:
echo           --wx-root    Specify the path to the wxWidgets source/libraries. Defaults
echo                        to %WXWIN%
echo           --wx-ver     The version of wxWidgets to build against, defaults to 30
echo.
echo      Examples:
echo           wxBuild_default.bat MINGW ALL
echo             Builds all targets with MinGW Gcc Compiler.
echo.
echo           wxBuild_default.bat VCTK LIB
echo             Builds just the static libraries with Visual C++ 7.1 Toolkit.
echo.
echo           wxBuild_default.bat VCTK NULL LIB_RELEASE_UNICODE
echo             Builds only the release static library with Visual C++ 7.1 Toolkit
goto END

:END
set PREMAKE=
set WXVER=
set PLATFORM=
set WXROOT=
set UNICODE=
set DYNAMIC_LINK=
set SHARED_LIBRARIES=
set ACTION=
set COMPILER_VERSION=
set MONOLITHIC=
set VCPLATFORM=
set MSBUILDPATH=
set BUILD_CMD_RELEASE=
set BUILD_CMD_DEBUG=
ENDLOCAL
