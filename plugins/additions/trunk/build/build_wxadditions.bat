@echo off
::**************************************************************************
:: File:           build_wxadditions.bat
:: Version:        1.04
:: Name:           RJP Computing 
:: Date:           08/11/2006
:: Description:    Use this to build all the projects for wxAdditions.
::                 Make sure to add the calls to any additions made to the
::                 wxAdditions library.
::
:: Prerequistes:   
::**************************************************************************

echo Generate all makefiles needed.
echo.
call bakefile_gen

:: -- AWX --
echo Building AWX with VC7.1
echo.
cd awx
call wxBuild_default VCTK ALL

echo Building AWX with MinGW Gcc
echo.
call wxBuild_default MINGW ALL
cd ..

:: -- wxPlot --
echo Building wxPlot with VC7.1
echo.
cd plot
call wxBuild_default VCTK ALL

echo Building wxPlot with MinGW Gcc
echo.
call wxBuild_default MINGW ALL
cd ..

:: -- wxPropGrid --
echo Building wxPropGrid with VC7.1
echo.
cd propgrid
call wxBuild_default VCTK ALL

echo Building wxPropGrid with MinGW Gcc
echo.
call wxBuild_default MINGW ALL
cd ..

:: -- wxFlatNotebook --
echo Building wxFlatNotebook with VC8.0
echo.
cd wxFlatNotebook
call wxBuild_wxFlatNotebook VC80 LIB

echo Building wxFlatNotebook with VC7.1
echo.
cd wxFlatNotebook
call wxBuild_wxFlatNotebook VCTK ALL

echo Building wxFlatNotebook with MinGW Gcc
echo.
call wxBuild_wxFlatNotebook MINGW ALL
cd ..

:: -- wxScintilla --
echo Building wxScintilla with VC7.1
echo.
cd wxScintilla
call wxBuild_default VCTK ALL

echo Building wxScintilla with MinGW Gcc
echo.
call wxBuild_default MINGW ALL
cd ..

:: -- wxThings --
echo Building wxThings with VC7.1
echo.
cd things
call wxBuild_default VCTK ALL

echo Building wxThings with MinGW Gcc
echo.
call wxBuild_default MINGW ALL
cd ..

:: -- wxPlotCtrl --
echo Building wxPlotCtrl with VC8.0
echo.
cd plotctrl
call wxBuild_plotctrl VC80 LIB

echo Building wxPlotCtrl with VC7.1
echo.
call wxBuild_plotctrl VCTK ALL

echo Building wxPlotCtrl with MinGW Gcc
echo.
call wxBuild_plotctrl MINGW ALL
cd ..

:: -- wxLedBarGraph --
echo Building wxLedBarGraph with VC7.1
echo.
cd ledBarGraph
call wxBuild_default VCTK ALL

echo Building wxLedBarGraph with MinGW Gcc
echo.
call wxBuild_default MINGW ALL
cd ..

:: -- wxFB Plugin --
echo Create the build files needed.
cd ..\wxfbPlugin
call create_build_files

echo Building wxFB Plugin with MinGW Gcc
echo.
call mingw32-make CONFIG=Release

echo Copy over need dll's to the wxAdditions plug-in directory
copy /Y ..\lib\gcc_dll\wxmsw28um_awx_gcc.dll wxAdditions\wxmsw28um_awx_gcc.dll
copy /Y ..\lib\gcc_dll\wxmsw28um_ledbargraph_gcc.dll wxAdditions\wxmsw28um_ledbargraph_gcc.dll
copy /Y ..\lib\gcc_dll\wxmsw28um_plotctrl_gcc.dll wxAdditions\wxmsw28um_plotctrl_gcc.dll
copy /Y ..\lib\gcc_dll\wxmsw28um_things_gcc.dll wxAdditions\wxmsw28um_things_gcc.dll
cd ..\build

::echo Clean up link libraries for MinGW Gcc.
::cd ..\lib\gcc_dll
::del /Q /F /S *.a
::cd ..\build

echo Done building wxAdditions.
