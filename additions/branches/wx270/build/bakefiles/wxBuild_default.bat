@echo off
::**************************************************************************
:: File:           wxBuild_default.bat
:: Version:        1.00
:: Name:           RJP Computing 
:: Date:           08/14/2006
:: Description:    Build wxWidgets things with the MinGW/Visual C++ ToolKit.
::                 
::**************************************************************************
set WXBUILD_VERSION=1.00
:: MinGW Gcc install lacation. This must match you systems configuration.
set GCCDIR=C:\MinGW

IF (%1) == () goto ERROR
:: -- Check if user wants help --
if (%1) == (/?)  goto SHOW_USAGE
if (%1) == (-?)  goto SHOW_USAGE
if (%1) == HELP  goto SHOW_USAGE
if (%1) == help  goto SHOW_USAGE
IF (%2) == () goto ERROR

:: -- Check which compiler was selected. --
if %1 == VCTK  goto SETUP_VC71_TOOLKIT_BUILD_ENVIRONMENT
if %1 == vctk  goto SETUP_VC71_TOOLKIT_BUILD_ENVIRONMENT
if %1 == MINGW  goto SETUP_GCC_BUILD_ENVIRONMENT
if %1 == mingw  goto SETUP_GCC_BUILD_ENVIRONMENT
goto COMPILER_ERROR


:SETUP_VC71_TOOLKIT_BUILD_ENVIRONMENT
:: -- Add Visual C++ directories to the systems PATH --
echo Setting environment for Visual C++ 7.1 Toolkit...
set MSVC=C:\Program Files\Microsoft Visual C++ Toolkit 2003
set MSSDK=C:\Program Files\Microsoft Platform SDK
set DOTNETSDK=C:\Program Files\Microsoft Visual Studio .NET 2003\vc7

set PATH=%MSVC%\bin;%MSSDK%\bin;%MSSDK%\bin\win64;%DOTNETSDK%\bin;%PATH%
set INCLUDE=%MSVC%\include;%MSSDK%\include;%DOTNETSDK%\include;%WXWIN%\include;%INCLUDE%
set LIB=%MSVC%\lib;%MSSDK%\lib;%DOTNETSDK%\lib;%LIB%
:: -- Setup the make executable and the actual makefile name --
set MAKE=nmake
set MAKEFILE=makefile.vc
goto START

:SETUP_GCC_BUILD_ENVIRONMENT
echo Assuming that MinGW has been installed to:
echo   %GCCDIR%
echo.
:: -- Add MinGW directory to the systems PATH --
echo Setting environment for MinGW Gcc...
if "%OS%" == "Windows_NT" set PATH=%GCCDIR%\BIN;%PATH%
if "%OS%" == "" set PATH="%GCCDIR%\BIN";"%PATH%"
echo.
:: -- Setup the make executable and the actual makefile name --
set MAKE=mingw32-make.exe
set MAKEFILE=makefile.gcc
goto START

:START
echo wxBuild_default v%WXBUILD_VERSION%
echo.

if %2 == LIB  goto LIB_BUILD
if %2 == lib  goto LIB_BUILD
if %2 == DLL  goto DLL_BUILD
if %2 == dll  goto DLL_BUILD
if %2 == ALL  goto ALL_BUILD
if %2 == all  goto ALL_BUILD
if %2 == CLEAN  goto CLEAN
if %2 == clean  goto CLEAN
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
goto LIB_BUILD

:CLEAN
echo Cleaning...
echo.
%MAKE% -f %MAKEFILE% clean
echo.
goto END

:LIB_BUILD
echo Building libs's...
echo.
goto LIB_DEBUG

:LIB_DEBUG
echo Compiling lib debug...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE% BUILD=debug SHARED=0 OFFICIAL_BUILD=1 RUNTIME_LIBS=static

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto LIB_RELEASE

:LIB_RELEASE
echo Compiling lib release...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE% BUILD=release SHARED=0 OFFICIAL_BUILD=1 RUNTIME_LIBS=static

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto LIB_BUILD_UNICODE

:LIB_BUILD_UNICODE
echo Building Unicode Lib's...
echo.
goto LIB_DEBUG_UNICODE

:LIB_DEBUG_UNICODE
echo Compiling lib debug Unicode...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=debug UNICODE=1 OFFICIAL_BUILD=1 RUNTIME_LIBS=static

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto LIB_RELEASE_UNICODE

:LIB_RELEASE_UNICODE
echo Compiling lib release Unicode...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=release UNICODE=1 OFFICIAL_BUILD=1 RUNTIME_LIBS=static

echo.
:: Check for build all
if %2 == all goto DLL_BUILD
if %2 == ALL goto DLL_BUILD
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto END

:DLL_BUILD
echo Building Dll's...
echo.
goto DLL_DEBUG

:DLL_DEBUG
echo Compiling dll debug...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=debug SHARED=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_RELEASE

:DLL_RELEASE
echo Compiling dll release...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=release SHARED=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_BUILD_UNICODE

:DLL_BUILD_UNICODE
echo Building Unicode Dll's...
echo.
goto DLL_DEBUG_UNICODE

:DLL_DEBUG_UNICODE
echo Compiling dll debug Unicode...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=debug SHARED=1 UNICODE=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_RELEASE_UNICODE

:DLL_RELEASE_UNICODE
echo Compiling dll release Unicode...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=release SHARED=1 UNICODE=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_BUILD_MONO

:DLL_BUILD_MONO
echo Building Monolithic Dll's...
echo.
goto DLL_DEBUG_MONO

:DLL_DEBUG_MONO
echo Compiling dll debug monolithic...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=debug MONOLITHIC=1 SHARED=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_RELEASE_MONO

:DLL_RELEASE_MONO
echo Compiling dll release monolithic...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=release MONOLITHIC=1 SHARED=1 OFFICIAL_BUILD=1

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
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=debug MONOLITHIC=1 SHARED=1 UNICODE=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_RELEASE_MONO_UNICODE

:DLL_RELEASE_MONO_UNICODE
echo Compiling dll release Unicode monolithic...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=release MONOLITHIC=1 SHARED=1 UNICODE=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto END

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

:SHOW_USAGE
echo.
echo wxBuild_default v%WXBUILD_VERSION%
echo     Build wxWidgets things with the MinGW/Visual C++ ToolKit.
echo.
echo Usage: "wxBuild_default.bat <Compiler{MINGW|VCTK}> <BuildTarget{LIB|DLL|ALL|CLEAN|NULL}> [Specific Option (See Below)]"
goto SHOW_OPTIONS

:SHOW_OPTIONS
echo.
echo      Compiler Options:
echo           MINGW = MinGW Gcc compiler
echo           VCTK  = Visual C++ 7.1 Toolkit
echo.
echo      BuildTarget Options:
echo           LIB   = Builds all the static library targets.
echo           DLL   = Builds all the dynamic library targets.
echo           ALL   = Builds all the targets (Recommended).
echo           CLEAN = Cleans the solution.
echo           NULL  = Used so that you can specify a specific target. (See below)
echo.
echo      Specific Options(Used with NULL): 
echo           LIB_DEBUG, LIB_RELEASE, LIB_DEBUG_UNICODE, LIB_RELEASE_UNICODE,
echo            DLL_DEBUG, DLL_RELEASE, DLL_DEBUG_UNICODE, DLL_RELEASE_UNICODE,
echo           DLL_DEBUG_MONO, DLL_RELEASE_MONO, DLL_DEBUG_MONO_UNICODE,
echo            DLL_RELEASE_MONO_UNICODE
echo.
echo      Examples:
echo           wxBuild_default.bat MINGW ALL
echo             Builds all targets with MinGW Gcc Compiler.
echo.
echo           wxBuild_default.bat VCTK LIB
echo             Builds just the static libraries with Visual C++ 7.1 Toolkit.
echo.
echo           wxBuild_default.bat VCTK NULL LIB_RELEASE
echo             Builds only the release static library with Visual C++ 7.1 Toolkit
goto END

:END
set WXBUILD_VERSION=
set GccDir=
set MAKE=
set MAKEFILE=
