@echo off
::**************************************************************************
:: File:           awx.bat
:: Version:        1.01
:: Name:           RJP Computing 
:: Date:           05/12/2006
:: Description:    Build AWX with the Visual C++ ToolKit.
::                 
::**************************************************************************
IF (%1) == () GOTO ERROR

set MSVC=C:\Program Files\Microsoft Visual C++ Toolkit 2003
set MSSDK=C:\Program Files\Microsoft Platform SDK
set DOTNETSDK=C:\Program Files\Microsoft Visual Studio .NET 2003\vc7

set PATH=%MSVC%\bin;%MSSDK%\bin;%MSSDK%\bin\win64;%DOTNETSDK%\bin;%PATH%
set INCLUDE=%MSVC%\include;%MSSDK%\include;%DOTNETSDK%\include;%INCLUDE%
set LIB=%MSVC%\lib;%MSSDK%\lib;%DOTNETSDK%\lib;%LIB%

echo.
echo "Compiling AWX"
echo.
nmake -f makefile.vc cleanobj

IF %1 == clean GOTO CLEAN
IF %1 == CLEAN GOTO CLEAN
if %1 == ALL  goto ALL_BUILD
if %1 == all  goto ALL_BUILD
IF %1 == LIB_DEBUG  GOTO LIB_DEBUG
IF %1 == LIB_RELEASE  GOTO LIB_RELEASE
IF %1 == LIB_DEBUG_UNICODE  GOTO LIB_DEBUG_UNICODE
IF %1 == LIB_RELEASE_UNICODE  GOTO LIB_RELEASE_UNICODE
IF %1 == LIB_DEBUG_USINGDLL  GOTO LIB_DEBUG_USINGDLL
IF %1 == LIB_RELEASE_USINGDLL  GOTO LIB_RELEASE_USINGDLL
IF %1 == LIB_DEBUG_UNICODE_USINGDLL  GOTO LIB_DEBUG_UNICODE_USINGDLL
IF %1 == LIB_RELEASE_UNICODE_USINGDLL  GOTO LIB_RELEASE_UNICODE_USINGDLL
IF %1 == DLL_DEBUG  GOTO DLL_DEBUG
IF %1 == DLL_RELEASE  GOTO DLL_RELEASE
goto WRONGPARAM

:ALL_BUILD
echo "Compiling all versions."
echo.
goto LIB_DEBUG

:CLEAN
echo Cleaning...
echo.
nmake -f makefile.vc clean
echo.
goto END

:LIB_DEBUG
echo Compiling AWX lib debug...
echo.
:: Calling the VisualC++ make > vc_lib_debug.txt
nmake -f makefile.vc WX_DEBUG=1 WX_SHARED=0 WX_VERSION=26
echo.

::echo Opening vc_lib_debug.txt...
::vc_lib_debug.txt
echo.
:: Check for build all
if %1 == ALL goto LIB_RELEASE
if %1 == all goto LIB_RELEASE
goto END

:LIB_RELEASE
echo Compiling AWX lib release...
echo.
:: Calling the VisualC++ make > vc_lib_release.txt
nmake -f makefile.vc WX_DEBUG=0 WX_SHARED=0 WX_VERSION=26
echo.

::echo Opening vc_lib_release.txt...
::vc_lib_release.txt
echo.
:: Check for build all
if %1 == ALL goto LIB_UNICODE_DEBUG
if %1 == all goto LIB_UNICODE_DEBUG
goto END

:LIB_UNICODE_DEBUG
echo Compiling AWX lib unicode debug...
echo.
:: Calling the VisualC++ make > vc_lib_debug.txt
nmake -f makefile.vc WX_DEBUG=1 WX_SHARED=0 WX_VERSION=26 WX_UNICODE=1
echo.

::echo Opening vc_lib_debug.txt...
::vc_lib_debug.txt
echo.
:: Check for build all
if %1 == ALL goto LIB_UNICODE_RELEASE
if %1 == all goto LIB_UNICODE_RELEASE
goto END

:LIB_UNICODE_RELEASE
echo Compiling AWX lib unicode release...
echo.
:: Calling the VisualC++ make > vc_lib_release.txt
nmake -f makefile.vc WX_DEBUG=0 WX_SHARED=0 WX_VERSION=26 WX_UNICODE=1
echo.

::echo Opening vc_lib_release.txt...
::vc_lib_release.txt
echo.
:: Check for build all
if %1 == ALL goto LIB_DEBUG_USINGDLL
if %1 == all goto LIB_DEBUG_USINGDLL
goto END

:LIB_DEBUG_USINGDLL
echo Compiling lib debug using dll...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  WX_DEBUG=1 CFG=dll WX_SHARED=0 USE_DLL=1

echo.
:: Check for build all
if %1 == ALL goto LIB_RELEASE_USINGDLL
if %1 == all goto LIB_RELEASE_USINGDLL
goto END

:LIB_RELEASE_USINGDLL
echo Compiling lib release using dll...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  WX_DEBUG=0 CFG=dll WX_SHARED=0 USE_DLL=1

echo.
:: Check for build all
if %1 == ALL goto LIB_DEBUG_UNICODE_USINGDLL
if %1 == all goto LIB_DEBUG_UNICODE_USINGDLL
goto END

:LIB_DEBUG_UNICODE_USINGDLL
echo Compiling lib unicode debug using dll...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  WX_DEBUG=1 CFG=dll WX_SHARED=0 USE_DLL=1 WX_UNICODE=1

echo.
:: Check for build all
if %1 == ALL goto LIB_RELEASE_UNICODE_USINGDLL
if %1 == all goto LIB_RELEASE_UNICODE_USINGDLL
goto END

:LIB_RELEASE_UNICODE_USINGDLL
echo Compiling lib unicode release using dll...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  WX_DEBUG=0 CFG=dll WX_SHARED=0 USE_DLL=1 WX_UNICODE=1

echo.
:: Check for build all
if %1 == ALL goto DLL_DEBUG
if %1 == all goto DLL_DEBUG
goto END

:DLL_DEBUG
echo Compiling AWX dll debug...
echo.
:: Calling the VisualC++ make > vc_dll_debug.txt
nmake -f makefile.vc  WX_DEBUG=1 WX_SHARED=1 WX_VERSION=26
echo.

::echo Opening vc_dll_debug.txt...
::vc_dll_debug.txt
echo.
:: Check for build all
if %1 == ALL goto DLL_RELEASE
if %1 == all goto DLL_RELEASE
goto END

:DLL_RELEASE
echo Compiling AWX dll release...
echo.
:: Calling the VisualC++ make > vc_dll_release.txt
nmake -f makefile.vc  WX_DEBUG=0 WX_SHARED=1 WX_VERSION=26
echo.

::echo Opening vc_dll_release.txt...
::vc_dll_release.txt
echo.
goto END

:ERROR
echo.
echo ERROR OCCURED!
echo Not enough command line parameters.
echo      Options: LIB_DEBUG, LIB_RELEASE, DLL_DEBUG, DLL_RELEASE, CLEAN
echo.
goto END

:WRONGPARAM
echo.
echo ERROR OCCURED!
echo The command line parameters was %1. This is not an available option.
echo      Options: LIB_DEBUG, LIB_RELEASE, DLL_DEBUG, DLL_RELEASE, CLEAN
echo.
goto END

:END
