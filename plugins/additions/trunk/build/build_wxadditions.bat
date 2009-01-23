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

echo Generate all makefiles needed.
echo.
call bakefile_gen

:: -- AWX --
echo Building AWX with VC8.0
echo.
cd awx
call wxBuild_default VC80 ALL

echo Building AWX with MinGW Gcc
echo.
call wxBuild_default MINGW4 ALL
cd ..

:: -- wxPlot --
echo Building wxPlot with VC8.0
echo.
cd plot
call wxBuild_default VC80 ALL

echo Building wxPlot with MinGW Gcc
echo.
call wxBuild_default MINGW4 ALL
cd ..

:: -- wxPropGrid --
echo Building wxPropGrid with VC8.0
echo.
cd propgrid
call wxBuild_default VC80 ALL

echo Building wxPropGrid with MinGW Gcc
echo.
call wxBuild_default MINGW4 ALL
cd ..

:: -- wxFlatNotebook --
echo Building wxFlatNotebook with VC8.0
echo.
cd wxFlatNotebook
call wxBuild_wxFlatNotebook VC80 ALL

echo Building wxFlatNotebook with MinGW Gcc
echo.
call wxBuild_wxFlatNotebook MINGW4 ALL
cd ..

:: -- wxScintilla --
echo Building wxScintilla with VC8.0
echo.
cd wxScintilla
call wxBuild_default VC80 ALL

echo Building wxScintilla with MinGW Gcc
echo.
call wxBuild_default MINGW4 ALL
cd ..

:: -- wxThings --
echo Building wxThings with VC8.0
echo.
cd things
call wxBuild_default VC80 ALL

echo Building wxThings with MinGW Gcc
echo.
call wxBuild_default MINGW4 ALL
cd ..

:: -- wxTreeListCtrl --
echo Building wxTreeListCtrl with VC8.0
echo.
cd treelistctrl
call wxBuild_default VC80 ALL

echo Building wxTreeListCtrl with MinGW Gcc
echo.
call wxBuild_default MINGW4 ALL
cd ..


:: -- wxPlotCtrl --
echo Building wxPlotCtrl with VC8.0
echo.
cd plotctrl
call wxBuild_plotctrl VC80 ALL

echo Building wxPlotCtrl with MinGW Gcc
echo.
call wxBuild_plotctrl MINGW4 ALL
cd ..

:: -- wxLedBarGraph --
echo Building wxLedBarGraph with VC8.0
echo.
cd ledBarGraph
call wxBuild_default VC80 ALL

echo Building wxLedBarGraph with MinGW Gcc
echo.
call wxBuild_default MINGW4 ALL
cd ..

:: -- wxFB Plugin --
echo Create the build files needed.
cd ..\wxfbPlugin
call create_build_files

echo Building wxFB Plugin with MinGW Gcc
echo.
echo Building using the wxWidgets directory %WXWIN%
call mingw32-make CONFIG=Release

echo Copy over need dll's to the wxAdditions plug-in directory
copy /Y ..\lib\gcc_dll\wxmsw28um_awx_gcc.dll wxAdditions\wxmsw28um_awx_gcc.dll
copy /Y ..\lib\gcc_dll\wxmsw28um_ledbargraph_gcc.dll wxAdditions\wxmsw28um_ledbargraph_gcc.dll
copy /Y ..\lib\gcc_dll\wxmsw28um_plotctrl_gcc.dll wxAdditions\wxmsw28um_plotctrl_gcc.dll
copy /Y ..\lib\gcc_dll\wxmsw28um_things_gcc.dll wxAdditions\wxmsw28um_things_gcc.dll
copy /Y ..\lib\gcc_dll\wxmsw28um_treelistctrl_gcc.dll wxAdditions\wxmsw28um_treelistctrl_gcc.dll
cd ..\build

::echo Clean up link libraries for MinGW Gcc.
::cd ..\lib\gcc_dll
::del /Q /F /S *.a
::cd ..\build

echo Done building wxAdditions.
pause
