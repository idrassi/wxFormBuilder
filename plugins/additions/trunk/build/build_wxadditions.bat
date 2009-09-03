@echo off
::**************************************************************************
:: File:           build_wxadditions.bat
:: Version:        1.06
:: Name:           RJP Computing 
:: Date:           07/25/2008
:: Description:    Use this to build all the projects for wxAdditions.
::                 Make sure to add the calls to any additions made to the
::                 wxAdditions library.
::
:: Prerequistes:   
::**************************************************************************

if (%1) == () goto ERROR
:: -- Check if user wants help --
if (%1) == (/?)  goto SHOW_USAGE
if (%1) == (-?)  goto SHOW_USAGE
if (%1) == HELP  goto SHOW_USAGE
if (%1) == help  goto SHOW_USAGE
if (%2) == ()    goto ERROR

echo Generate all makefiles needed.
echo.
call bakefile_gen

:: -- AWX --
echo Building AWX with %1
echo.
cd awx
call wxBuild_default %1 ALL
call wxBuild_default %1 MOVE
cd ..

:: -- wxPlot --
echo Building wxPlot with %1
echo.
cd plot
call wxBuild_default %1 ALL
call wxBuild_default %1 MOVE
cd ..

:: -- wxPropGrid --
echo Building wxPropGrid with %1
echo.
cd propgrid
call wxBuild_default %1 ALL
call wxBuild_default %1 MOVE
cd ..

:: -- wxFlatNotebook --
echo Building wxFlatNotebook with %1
echo.
cd wxFlatNotebook
::call wxBuild_wxFlatNotebook %1 ALL
call wxBuild_default %1 ALL
call wxBuild_default %1 MOVE
cd ..

:: -- wxScintilla --
echo Building wxScintilla with %1
echo.
cd wxScintilla
call wxBuild_default %1 ALL
call wxBuild_default %1 MOVE
cd ..

:: -- wxThings --
echo Building wxThings with %1
echo.
cd things
call wxBuild_default %1 ALL
call wxBuild_default %1 MOVE
cd ..

:: -- wxTreeListCtrl --
echo Building wxTreeListCtrl with %1
echo.
cd treelistctrl
call wxBuild_default %1 ALL
call wxBuild_default %1 MOVE
cd ..

:: -- wxPlotCtrl --
echo Building wxPlotCtrl with %1
echo.
cd plotctrl
::call wxBuild_plotctrl %1 ALL
call wxBuild_default %1 ALL
call wxBuild_default %1 MOVE
cd ..

:: -- wxLedBarGraph --
echo Building wxLedBarGraph with %1
echo.
cd ledBarGraph
call wxBuild_default %1 ALL
call wxBuild_default %1 MOVE
cd ..

::echo Clean up link libraries for MinGW Gcc.
::cd ..\lib\gcc_dll
::del /Q /F /S *.a
::cd ..\build

echo Done building wxAdditions.
goto END

:ERROR
echo.
echo ERROR OCCURED!
echo Not enough command line parameters.
goto SHOW_USAGE

:SHOW_USAGE
echo.
echo Usage: "wxBuild_default.bat <Compiler{MINGW|VCTK|VC71|VC80|VC90}>"
goto SHOW_OPTIONS

:SHOW_OPTIONS
echo.
echo      Compiler Options:
echo           MINGW  = MinGW Gcc v3.x.x compiler
echo           MINGW4 = MinGW Gcc v4.x.x compiler
echo           VCTK   = Visual C++ 7.1 Toolkit
echo           VC71   = Visual C++ 7.1
echo           VC80   = Visual C++ 8.0
echo           VC90   = Visual C++ 9.0
echo.
goto END

:END

