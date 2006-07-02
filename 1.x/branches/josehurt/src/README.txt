Compiling wxFormBuilder
-----------------------

In order to compile wxFormBuilder you need these libraries:

- wxWidgets - 2.5.4 (**new**)
 
- boost     - 1.31
  Used only for automatic memory management with "smart pointers".
  See http://www.boost.org/libs/smart_ptr/shared_ptr.htm for more info.

- tinyxml   - 2.3.2
  Used for loading/saving XML files.


Change appropiate paths on Makefile for Linux, or into Dev-C++ project
settings for Windows.

NOTES:
  1. You don't have to build boost libraries (it only uses header files).
  2. compile tinyxml as a static library with -DTINYXML_USE_STL
     (copy Makefile.tinyxml into tinyxml sources and build it)


On Linux I use this path structure:

--------------------------------------------------------------
<project>
    +- src
        +- xml : all xml files
        +- xpm : all icon files
        +- projects
              +- example  : example projects
    +- libs
         +- boost_1_31_0  : boost library
         +- tinyxml       : tinyxml library
         
--------------------------------------------------------------     
     
Enjoy :-)


José Antonio Hurtado.

joseantonio.hurtado@hispalinux.es

2005-03-19

