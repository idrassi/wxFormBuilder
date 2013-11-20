@echo off

premake\premake-win32.exe --target cb-gcc --unicode --with-wx-shared
echo done...
echo.

rem premake\premake-win32.exe --target cl-gcc --unicode --with-wx-shared
rem echo done...
rem echo.

premake\premake-win32.exe --target gnu --unicode --with-wx-shared
echo done...
echo.

echo Done generating all project files for wxFormBuilder.