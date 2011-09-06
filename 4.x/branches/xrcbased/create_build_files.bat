@echo off

premake4\windows\premake4.exe --file=premake4/solution.lua codelite
echo done...
echo.

premake4\windows\premake4.exe --file=premake4/solution.lua gmake
echo done...
echo.

echo Done generating all project files for wxFormBuilder.

