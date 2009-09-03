@echo off
::**************************************************************************
:: File:			wxBuild_default.bat
:: Version:			1.06
:: Name:			RJP Computing 
:: Date:			09/03/2009
:: Description:		Build wxWidgets things with the MinGW/Visual C++.
::                 
::                 	v1.01 - Added Compiler setup for VC7.1 and VC8.0.
::                 	v1.02 - Added INCLUDE variable to VC7.1 and VC8.0 setups.
:: 					v1.03 - Added FLAGS. Use to set extra command line options.
:: 					v1.04 - Added MinGW Gcc 4.x.x compiler.
:: 					v1.05 - Removed wchar_t setting from VC8.0 setup.
:: 					v1.06 - Added VC9.0 compiler setup.
::**************************************************************************
set WXBUILD_VERSION=1.05
:: MinGW Gcc install location. This must match you systems configuration.
set GCCDIR=C:\MinGW
set GCC4DIR=C:\MinGW4

if (%1) == () goto ERROR
:: -- Check if user wants help --
if (%1) == (/?)  goto SHOW_USAGE
if (%1) == (-?)  goto SHOW_USAGE
if (%1) == HELP  goto SHOW_USAGE
if (%1) == help  goto SHOW_USAGE
if (%2) == ()    goto ERROR

:: -- Check which compiler was selected. --
if %1 == VCTK   goto SETUP_VC71_TOOLKIT_BUILD_ENVIRONMENT
if %1 == vctk   goto SETUP_VC71_TOOLKIT_BUILD_ENVIRONMENT
if %1 == VC71   goto SETUP_VC71_BUILD_ENVIRONMENT
if %1 == vc71   goto SETUP_VC71_BUILD_ENVIRONMENT
if %1 == VC80   goto SETUP_VC80_BUILD_ENVIRONMENT
if %1 == vc80   goto SETUP_VC80_BUILD_ENVIRONMENT
if %1 == VC90   goto SETUP_VC90_BUILD_ENVIRONMENT
if %1 == vc90   goto SETUP_VC90_BUILD_ENVIRONMENT
if %1 == MINGW  goto SETUP_GCC_BUILD_ENVIRONMENT
if %1 == mingw  goto SETUP_GCC_BUILD_ENVIRONMENT
if %1 == MINGW4  goto SETUP_GCC4_BUILD_ENVIRONMENT
if %1 == mingw4  goto SETUP_GCC4_BUILD_ENVIRONMENT
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
set FLAGS=
goto START

:SETUP_VC71_BUILD_ENVIRONMENT
:: Add the full VC 2003 .net includes.
echo Setting environment for Visual C++ 7.1...
echo.
call "C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
set INCLUDE=%WXWIN%\include;%INCLUDE%
:: -- Setup the make executable and the actual makefile name --
set MAKE=nmake
set MAKEFILE=makefile.vc
set FLAGS=
goto START


:SETUP_VC80_BUILD_ENVIRONMENT
:: Add the full VC 2005 includes.
echo Setting environment for Visual C++ 8.0...
echo.
call "%VS80COMNTOOLS%vsvars32.bat"
set INCLUDE=%WXWIN%\include;%INCLUDE%
:: -- Setup the make executable and the actual makefile name --
set MAKE=nmake
set MAKEFILE=makefile.vc
set FLAGS=
goto START

:SETUP_VC90_BUILD_ENVIRONMENT
:: Add the VC 2008 includes.
echo Setting environment for Visual C++ 9.0...
echo.
call "%VS90COMNTOOLS%vsvars32.bat"
set INCLUDE=%WXWIN%\include;%INCLUDE%
:: -- Setup the make executable and the actual makefile name --
set MAKE=nmake
set MAKEFILE=makefile.vc
set FLAGS=USE_ODBC=1 USE_OPENGL=1 USE_QA=1 USE_GDIPLUS=1
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
set FLAGS=-j %NUMBER_OF_PROCESSORS%
goto START

:SETUP_GCC4_BUILD_ENVIRONMENT
echo Assuming that MinGW has been installed to:
echo   %GCC4DIR%
echo.
:: -- Add MinGW directory to the systems PATH --
echo Setting environment for MinGW Gcc v4.x.x...
if "%OS%" == "Windows_NT" set PATH=%GCC4DIR%\BIN;%PATH%
if "%OS%" == "" set PATH="%GCC4DIR%\BIN";"%PATH%"
echo.
:: -- Setup the make executable and the actual makefile name --
set MAKE=mingw32-make.exe
set MAKEFILE=makefile.gcc
set FLAGS=CXXFLAGS=-Wno-attributes -j %NUMBER_OF_PROCESSORS%
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
if %2 == MOVE  goto MOVE
if %2 == move  goto MOVE
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

:MOVE
echo Moving binary files...
echo.
if %1 == VCTK   goto MOVE_VCTK
if %1 == vctk   goto MOVE_VCTK
if %1 == VC71   goto MOVE_VCTK
if %1 == vc71   goto MOVE_VCTK
if %1 == VC80   goto MOVE_VC80
if %1 == vc80   goto MOVE_VC80
if %1 == VC90   goto MOVE_VC90
if %1 == vc90   goto MOVE_VC90
if %1 == MINGW  goto MOVE_MINGW
if %1 == mingw  goto MOVE_MINGW
if %1 == MINGW4  goto MOVE_MINGW4
if %1 == mingw4  goto MOVE_MINGW4
goto MOVE_ERROR

:MOVE_VCTK
:: Move Visual C++ 7.1 directories.
if exist ..\..\lib\vc_lib move /Y ..\..\lib\vc_lib ..\..\lib\vc7_lib
if exist ..\..\lib\vc_dll move /Y ..\..\lib\vc_dll ..\..\lib\vc7_dll
echo.
goto END

:MOVE_VC80
:: Move Visual C++ 8.0 directories.
if exist ..\..\lib\vc_lib move /Y ..\..\lib\vc_lib ..\..\lib\vc8_lib
if exist ..\..\lib\vc_dll move /Y ..\..\lib\vc_dll ..\..\lib\vc8_dll
echo.
goto END

:MOVE_VC90
:: Move Visual C++ 9.0 directories.
if exist ..\..\lib\vc_lib move /Y ..\..\lib\vc_lib ..\..\lib\vc9_lib
if exist ..\..\lib\vc_dll move /Y ..\..\lib\vc_dll ..\..\lib\vc9_dll
echo.
goto END

:MOVE_MINGW
:: Move MinGW 3.x.x directories.
if exist ..\..\lib\gcc_lib move /Y ..\..\lib\gcc_lib ..\..\lib\gcc3_lib
if exist ..\..\lib\gcc_dll move /Y ..\..\lib\gcc_dll ..\..\lib\gcc3_dll
echo.
goto END

:MOVE_MINGW4
:: Move MinGW 4.x.x directories.
if exist ..\..\lib\gcc_lib move /Y ..\..\lib\gcc_lib ..\..\lib\gcc4_lib
if exist ..\..\lib\gcc_dll move /Y ..\..\lib\gcc_dll ..\..\lib\gcc4_dll
echo.
goto END

:LIB_BUILD
echo Building libs's...
echo.
goto LIB_DEBUG

:LIB_DEBUG
echo Compiling lib debug...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE% BUILD=debug SHARED=0 OFFICIAL_BUILD=1 RUNTIME_LIBS=static %FLAGS%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto LIB_RELEASE

:LIB_RELEASE
echo Compiling lib release...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE% BUILD=release SHARED=0 OFFICIAL_BUILD=1 RUNTIME_LIBS=static %FLAGS%

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
%MAKE% -f %MAKEFILE%  BUILD=debug UNICODE=1 OFFICIAL_BUILD=1 RUNTIME_LIBS=static %FLAGS%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto LIB_RELEASE_UNICODE

:LIB_RELEASE_UNICODE
echo Compiling lib release Unicode...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=release UNICODE=1 OFFICIAL_BUILD=1 RUNTIME_LIBS=static %FLAGS%

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
%MAKE% -f %MAKEFILE%  BUILD=debug SHARED=1 OFFICIAL_BUILD=1 %FLAGS%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_RELEASE

:DLL_RELEASE
echo Compiling dll release...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=release SHARED=1 OFFICIAL_BUILD=1 %FLAGS%

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
%MAKE% -f %MAKEFILE%  BUILD=debug SHARED=1 UNICODE=1 OFFICIAL_BUILD=1 %FLAGS%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_RELEASE_UNICODE

:DLL_RELEASE_UNICODE
echo Compiling dll release Unicode...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=release SHARED=1 UNICODE=1 OFFICIAL_BUILD=1 %FLAGS%

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
%MAKE% -f %MAKEFILE%  BUILD=debug MONOLITHIC=1 SHARED=1 OFFICIAL_BUILD=1 %FLAGS%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_RELEASE_MONO

:DLL_RELEASE_MONO
echo Compiling dll release monolithic...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=release MONOLITHIC=1 SHARED=1 OFFICIAL_BUILD=1 %FLAGS%

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
%MAKE% -f %MAKEFILE%  BUILD=debug MONOLITHIC=1 SHARED=1 UNICODE=1 OFFICIAL_BUILD=1 %FLAGS%

echo.
:: Check for specific mode.
if %2 == null goto END
if %2 == NULL goto END
goto DLL_RELEASE_MONO_UNICODE

:DLL_RELEASE_MONO_UNICODE
echo Compiling dll release Unicode monolithic...
:: Calling the compilers  make
%MAKE% -f %MAKEFILE%  BUILD=release MONOLITHIC=1 SHARED=1 UNICODE=1 OFFICIAL_BUILD=1 %FLAGS%

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
echo Usage: "wxBuild_default.bat <Compiler{MINGW|VCTK|VC71|VC80|VC90}> <BuildTarget{LIB|DLL|ALL|CLEAN|NULL}> [Specific Option (See Below)]"
goto SHOW_OPTIONS

:SHOW_OPTIONS
echo.
echo      Compiler Options:
echo           MINGW = MinGW Gcc v3.x.x compiler
echo           MINGW4 = MinGW Gcc v4.x.x compiler
echo           VCTK  = Visual C++ 7.1 Toolkit
echo           VC71  = Visual C++ 7.1
echo           VC80  = Visual C++ 8.0
echo           VC90  = Visual C++ 9.0
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
set GCCDIR=
set GCC4DIR=
set MAKE=
set MAKEFILE=
set FLAGS=
