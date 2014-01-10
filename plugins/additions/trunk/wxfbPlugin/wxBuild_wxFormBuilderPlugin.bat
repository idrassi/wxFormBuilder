@echo off
::**************************************************************************
:: File:           wxBuild_wxFormBuilderPlugin.bat
:: Version:        1.00
:: Name:           Chris Steenwyk - Generated for use with Premake4
:: Date:           11/20/2013
:: Description:    Build wxFormBuilderPlugin with the MinGW4-w64
::                 
::**************************************************************************
SETLOCAL
set WXBUILD_VERSION=1.00
set WXBUILD_APPNAME=wxBuild_wxFormBuilderPlugin
:: MinGW4-w64 Gcc install location. This must match your systems configuration.
set MINGW4_W64_DIR=C:\GCC\MinGW-w64\4.8.1
set MINGW4_W64_GCC4VER=48

::Configuration Parameters
set PREMAKE=..\build\premake\windows\premake4.exe
set WXVER=30
set WXROOT=%WXWIN%
set ACTION=
set COMPILER_VERSION=

:Loop
IF [%1]==[--wx-root]                  GOTO WxRoot
IF [%1]==[--wx-version]               GOTO WxVersion

goto SETUP_MINGW4_W64_BUILD_ENVIRONMENT

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
:PREMAKE
echo %PREMAKE% --targetdir-base=./ --compiler-version=%COMPILER_VERSION% --wx-root=%WXROOT% --wx-version=%WXVER% --wx-shared --monolithic --unicode %ACTION%
%PREMAKE% --targetdir-base=./ --compiler-version=%COMPILER_VERSION% --wx-root=%WXROOT% --wx-version=%WXVER% --wx-shared --monolithic --unicode %ACTION%

echo.
exit /b

:GENERATE_BUILD_CMD_MINGW
echo Assuming that MinGW-w64 has been installed to:
echo   %MINGW4_W64_DIR%
echo.
if "%OS%" == "Windows_NT" set PATH=%MINGW4_W64_DIR%\BIN;%PATH%
if "%OS%" == "" set PATH="%MINGW4_W64_DIR%\BIN";"%PATH%"
set CMDSUFFIX=32
set BUILD_CMD_RELEASE=mingw32-make config=release
set BUILD_CMD_DEBUG=mingw32-make config=debug
exit /b

::**************************************************************************
:: Compiler Config
::**************************************************************************

:SETUP_MINGW4_W64_BUILD_ENVIRONMENT
echo Setting environment for MinGW4-w64 64-bit...
set ACTION=gmake
set COMPILER_VERSION=%MINGW4_W64_GCC4VER%
call :GENERATE_BUILD_CMD_MINGW
goto START

::**************************************************************************
:: Build Steps
::**************************************************************************

:START
echo %WXBUILD_APPNAME% v%WXBUILD_VERSION%
echo.
call :PREMAKE
%BUILD_CMD_RELEASE%
goto COPY_DLL

:COPY_DLL
echo Copying DLLs for plugin...
copy ..\gcc%COMPILER_VERSION%_dll\*um_*.dll wxAdditions
goto END

:END
set PREMAKE=
set WXVER=
set WXROOT=
set ACTION=
set COMPILER_VERSION=
set BUILD_CMD_RELEASE=
set BUILD_CMD_DEBUG=
ENDLOCAL
