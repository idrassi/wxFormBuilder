@ECHO OFF

REM Clear output
CLS

REM Set Defaults
SET unicode=--unicode
SET wxroot=
SET wxver=28
SET compiler=gmake
SET arch=x32
SET shared="--wx-shared"
SET compiler_version=
SET build_shared=

REM Handle parameters
:Loop
REM Show help and exit
IF [%1]==[-h]                   GOTO Help
IF [%1]==[--help]               GOTO Help
IF [%1]==[--compiler]           GOTO Compiler
IF [%1]==[--compiler-version]   GOTO CompilerVersion
IF [%1]==[--arch]               GOTO Arch
IF [%1]==[--wx-root]            GOTO Root
IF [%1]==[--disable-unicode]    GOTO Unicode
IF [%1]==[--wx-version]         GOTO Version
IF [%1]==[--disable-shared]     GOTO Shared
GOTO Premake

:Help
ECHO.
ECHO Available options:
ECHO.
ECHO --compiler             Specify compiler used.
ECHO                        Example: --compiler=vc2012 if you use MSVC 2012.
ECHO                        Current: %compiler%
ECHO.
ECHO --compiler-version     Specify compiler version, used for linking in GCC. GCC Only
ECHO                        Example: --compiler-version=48 if you use MinGW4 4.8.
ECHO.
ECHO --arch                 Specify target architecture (x32 or x64)
ECHO                        Example: --arch=x64 to generate 64-bit files
ECHO                        Current: %arch%
ECHO.
ECHO --disable-shared       Use static wxWidgets build instead of shared libraries.
ECHO.
ECHO --disable-unicode      Whether to use an Unicode or an ANSI build.
ECHO                        Ignored in wxWidgets 2.9 and later.
ECHO                        Example: --disable-unicode produces an ANSI build.
ECHO                        Default: Unicode build on all versions.
ECHO.
ECHO --wx-root              Specify the wxWidgets build path,
ECHO                        useful for wxWidgets builds not installed
ECHO                        in your system (alternate/custom builds)
ECHO                        Example: --wx-root=D:\Devel\wxWidgets\3.0
ECHO                        Current: %WXWIN%
ECHO.
ECHO --wx-version           Specify the wxWidgets version.
ECHO                        Example: --wx-version=29
ECHO                        Default: %wxver%
ECHO.
GOTO End

:Compiler
SET compiler=%2
SHIFT
SHIFT
GOTO Loop

:CompilerVersion
SET compiler_version=--compiler-version=%2
SHIFT
SHIFT
GOTO Loop

:Arch
SET arch=%2
SHIFT
SHIFT
GOTO Loop

:Root
SET wxroot=--wx-root=%2
SHIFT
SHIFT
GOTO Loop

:Unicode
SET unicode=
SHIFT
GOTO Loop

:Version
SET wxver=%2
SHIFT
SHIFT
GOTO Loop

:Shared
SET shared=
SHIFT
GOTO Loop

:BuildShared
SET build_shared=--shared-libraries
SHIFT
GOTO Loop

:Premake
premake\windows\premake4.exe %shared% --wx-version=%wxver% --platform=%arch% %compiler_version% %unicode% %wxroot% %build_shared% %compiler%
ECHO.

ECHO Done generating all project files for wxAdditions.
:End

