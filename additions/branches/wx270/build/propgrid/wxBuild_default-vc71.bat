@echo off
::**************************************************************************
:: File:           wxBuild_default-vc71.bat
:: Version:        1.00
:: Name:           RJP Computing 
:: Date:           05/18/2006
:: Description:    Build wxWidgets things with the Visual C++ ToolKit.
::                 
::**************************************************************************
IF (%1) == () goto ERROR

set MSVC=C:\Program Files\Microsoft Visual C++ Toolkit 2003
set MSSDK=C:\Program Files\Microsoft Platform SDK
set DOTNETSDK=C:\Program Files\Microsoft Visual Studio .NET 2003\vc7

set PATH=%MSVC%\bin;%MSSDK%\bin;%MSSDK%\bin\win64;%DOTNETSDK%\bin;%PATH%
set INCLUDE=%MSVC%\include;%MSSDK%\include;%DOTNETSDK%\include;%WXWIN%\include;%INCLUDE%
set LIB=%MSVC%\lib;%MSSDK%\lib;%DOTNETSDK%\lib;%LIB%

echo wxBuild_default-vc71 v1.00
echo.

if %1 == LIB  goto LIB_BUILD
if %1 == lib  goto LIB_BUILD
if %1 == DLL  goto DLL_BUILD
if %1 == dll  goto DLL_BUILD
if %1 == ALL  goto ALL_BUILD
if %1 == all  goto ALL_BUILD
if %1 == CLEAN  goto CLEAN
if %1 == clean  goto CLEAN
if %1 == NULL  goto SECIFIC_BUILD
if %1 == null  goto SECIFIC_BUILD
goto WRONGPARAM

:SECIFIC_BUILD
echo Specific mode...
echo.
IF (%2) == () goto ERROR
goto %2

:ALL_BUILD
echo "Compiling all versions."
echo.
goto LIB_BUILD

:CLEAN
echo Cleaning...
echo.
nmake -f makefile.vc clean
echo.
goto END

:LIB_BUILD
echo Building libs's...
echo.
goto LIB_DEBUG

:LIB_DEBUG
echo Compiling lib debug...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc BUILD=debug SHARED=0 OFFICIAL_BUILD=1 RUNTIME_LIBS=static

echo.
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END
goto LIB_RELEASE

:LIB_RELEASE
echo Compiling lib release...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc BUILD=release SHARED=0 OFFICIAL_BUILD=1 RUNTIME_LIBS=static

echo.
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END
:: Check for build all
if %1 == ALL goto LIB_BUILD_UNICODE
if %1 == all goto LIB_BUILD_UNICODE

:LIB_BUILD_UNICODE
echo Building Unicode Lib's...
echo.
goto LIB_DEBUG_UNICODE

:LIB_DEBUG_UNICODE
echo Compiling lib debug Unicode...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  BUILD=debug UNICODE=1 OFFICIAL_BUILD=1 RUNTIME_LIBS=static

echo.
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END
goto LIB_RELEASE_UNICODE

:LIB_RELEASE_UNICODE
echo Compiling lib release Unicode...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  BUILD=release UNICODE=1 OFFICIAL_BUILD=1 RUNTIME_LIBS=static

echo.
:: Check for build all
if %1 == ALL goto DLL_BUILD
if %1 == all goto DLL_BUILD
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END
goto END

:DLL_BUILD
echo Building Dll's...
echo.
goto DLL_DEBUG

:DLL_DEBUG
echo Compiling dll debug...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  BUILD=debug SHARED=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END
goto DLL_RELEASE

:DLL_RELEASE
echo Compiling dll release...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  BUILD=release SHARED=1 OFFICIAL_BUILD=1

echo.
:: Check for build all
if %1 == ALL goto DLL_BUILD_UNICODE
if %1 == all goto DLL_BUILD_UNICODE
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END

:DLL_BUILD_UNICODE
echo Building Unicode Dll's...
echo.
goto DLL_DEBUG_UNICODE

:DLL_DEBUG_UNICODE
echo Compiling dll debug Unicode...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  BUILD=debug SHARED=1 UNICODE=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END
goto DLL_RELEASE_UNICODE

:DLL_RELEASE_UNICODE
echo Compiling dll release Unicode...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  BUILD=release SHARED=1 UNICODE=1 OFFICIAL_BUILD=1

echo.
:: Check for build all
if %1 == ALL goto DLL_BUILD_MONO
if %1 == all goto DLL_BUILD_MONO
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END

:DLL_BUILD_MONO
echo Building Monolithic Dll's...
echo.
goto DLL_DEBUG_MONO

:DLL_DEBUG_MONO
echo Compiling dll debug monolithic...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  BUILD=debug MONOLITHIC=1 SHARED=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END
goto DLL_RELEASE_MONO

:DLL_RELEASE_MONO
echo Compiling dll release monolithic...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  BUILD=release MONOLITHIC=1 SHARED=1 OFFICIAL_BUILD=1

echo.
:: Check for build all
if %1 == ALL goto DLL_BUILD_MONO_UNICODE
if %1 == all goto DLL_BUILD_MONO_UNICODE
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END

:DLL_BUILD_MONO_UNICODE
echo Building Monolithic Unicode Dll's...
echo.
goto DLL_DEBUG_MONO_UNICODE

:DLL_DEBUG_MONO_UNICODE
echo Compiling dll debug Unicode monolithic...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  BUILD=debug MONOLITHIC=1 SHARED=1 UNICODE=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END
goto DLL_RELEASE_MONO_UNICODE

:DLL_RELEASE_MONO_UNICODE
echo Compiling dll release Unicode monolithic...
echo.
:: Calling the VisualC++ make
nmake -f makefile.vc  BUILD=release MONOLITHIC=1 SHARED=1 UNICODE=1 OFFICIAL_BUILD=1

echo.
:: Check for specific mode.
if %1 == null goto END
if %1 == NULL goto END
goto END

:ERROR
echo.
echo ERROR OCCURED!
echo Not enough command line parameters.
echo      Options:
echo           LIB, DLL, ALL, CLEAN, NULL
echo.
echo      Specific Options(Used with NULL): 
echo           LIB_DEBUG, LIB_RELEASE, LIB_DEBUG_UNICODE, LIB_RELEASE_UNICODE,
echo            DLL_DEBUG, DLL_RELEASE, DLL_DEBUG_UNICODE, DLL_RELEASE_UNICODE,
echo           DLL_DEBUG_MONO, DLL_RELEASE_MONO, DLL_DEBUG_MONO_UNICODE,
echo            DLL_RELEASE_MONO_UNICODE
echo.
goto END

:WRONGPARAM
echo.
echo ERROR OCCURED!
echo The command line parameters was %1. This is not an available option.
echo      Options:
echo           LIB, DLL, ALL, CLEAN, NULL
echo.
echo      Specific Options(Used with NULL): 
echo           LIB_DEBUG, LIB_RELEASE, DLL_DEBUG, DLL_RELEASE,
echo           DLL_DEBUG_MONO, DLL_RELEASE_MONO
echo.
goto END

:END
echo Compiling done...
