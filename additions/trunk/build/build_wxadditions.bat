@echo off
::**************************************************************************
:: File:           build_wxadditions.bat
:: Version:        1.00
:: Name:           RJP Computing 
:: Date:           08/11/2006
:: Description:    Use this to build all the projects for wxAdditions.
::                 Make sure to add the calls to any additions made to the
::                 wxAdditions library.
::**************************************************************************

echo Generate all makefiles needed.
echo.
call bakefile_gen

echo Building awx with VC7.1
echo.
cd awx
call wxBuild_default VCTK ALL
cd ..

echo Building plot with VC7.1
echo.
cd plot
call wxBuild_default VCTK ALL
cd ..

echo Building propgrid with VC7.1
echo.
cd propgrid
call wxBuild_default VCTK ALL
cd ..

echo Building wxFlatNotebook with VC7.1
echo.
cd wxFlatNotebook
call wxBuild_default VCTK ALL
cd ..

echo Building wxScintilla with VC7.1
echo.
cd wxScintilla
call wxBuild_default VCTK ALL
cd ..

echo Building things with VC7.1
echo.
cd things
call wxBuild_default VCTK ALL
cd ..

echo Building plotctrl with VC8.0
echo.
cd plotctrl
call wxBuild_plotctrl VC80 LIB
cd ..

echo Building plotctrl with VC7.1
echo.
cd plotctrl
call wxBuild_plotctrl VCTK ALL
cd ..

echo Done building wxAdditions.
