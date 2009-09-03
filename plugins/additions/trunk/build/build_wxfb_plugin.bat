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

:: Change back to build directory of additions
cd ..\build
