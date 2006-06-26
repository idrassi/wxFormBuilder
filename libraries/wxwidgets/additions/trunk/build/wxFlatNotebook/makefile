###################################################################################################################
#
# Project: wxFlatNotebook
# Date: 1/23/2006 12:06AM
# Author: Eran Ifrah 
#
# gcc makefile for building wxFlatNotebook on Linux platform
# this makefile was tested under Linux FC4 GTK2+
# to make it work properly, make sure you have the environment variable WXSTABLE set to the installation of your wx
# include file path (e.g. /usr/local/include/wx-2.6/ )
#
# Usage:
# to run it in debug mode run
# make clean
# make type=debug
#
# for release build, simply run:
# make clean
# make 
###################################################################################################################

ifeq ($(type),debug)
   INCS =  -I../../include -I/usr/local/lib/wx/include/gtk2-ansi-debug-2.6 -I$(WXSTABLE)
   DEBUG_FLAG= d
   DEBUG_DEFS= -D__WXDEBUG__ 
   CMP  = g++ -g
else
   INCS =  -I../../include -I/usr/local/lib/wx/include/gtk2-ansi-release-2.6 -I$(WXSTABLE)
   DEBUG_FLAG=
   DEBUG_DEFS=
   CMP  = g++
endif

# Sample program objects
TEST_OBJ = Objects/App.o Objects/Frame.o Objects/resources.o

# Library object
OBJ  = Objects/wxFlatNotebook.o

# Libraries required to link the sample program and their path
LIBS =  -L/usr/local/lib  -lwx_gtk2$(DEBUG_FLAG)_xrc-2.6 -lwx_gtk2$(DEBUG_FLAG)_core-2.6  -lwx_base$(DEBUG_FLAG)-2.6    -L../../lib -lwxFlatNotebook$(DEBUG_FLAG)  -pthread   -L/usr/X11R6/lib -lz -ldl -lm  -pthread -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lm -lpangoxft-1.0 -lpangox-1.0 -lpango-1.0 -lgobject-2.0 -lgmodule-2.0 -ldl -lgthread-2.0 -lglib-2.0 -lXinerama -lXxf86vm -lpng -lz -ljpeg -ltiff

# sample program name
OUTPUT  = wxFlatNotebookTest

# library name
LIB_OUTPUT  = ../../lib/libwxFlatNotebook$(DEBUG_FLAG).a

# C++ flags to pass to the compiler
CXXFLAGS = $(INCS) $(DEFS) -fexpensive-optimizations -O3 -Wall -Wundef -Wno-ctor-dtor-privacy

# Additional defined to pass to the compiler
DEFS = -D__WXGTK__ -DWX_PRECOMP -DNO_GCC_PRAGMA -DXTHREADS -D_REENTRANT -DXUSE_MTSAFE_API -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -D_LARGEFILE_SOURCE=1 $(DEBUG_DEFS) -DWXUSINGDLL

# use this RM command
RM = rm -f

# Rules
wxFlatNotebookTest: wxFlatNotebook $(TEST_OBJ)
	$(CMP) -o $(OUTPUT) $(TEST_OBJ) $(LIBS)

wxFlatNotebook: $(OBJ)
	test -d Objects || mkdir Objects
	ar -r $(LIB_OUTPUT) $(OBJ)

Objects/wxFlatNotebook.o: ../../src/wxFlatNotebook/wxFlatNotebook.cpp
	$(CMP) $(CXXFLAGS) -c ../../src/wxFlatNotebook/wxFlatNotebook.cpp -o Objects/wxFlatNotebook.o

Objects/App.o: ../../samples/wxFlatNotebook/App.cpp
	test -d Objects || mkdir Objects
	$(CMP) $(CXXFLAGS) -c ../../samples/wxFlatNotebook/App.cpp -o Objects/App.o

Objects/Frame.o: ../../samples/wxFlatNotebook/Frame.cpp
	$(CMP) $(CXXFLAGS) -c ../../samples/wxFlatNotebook/Frame.cpp -o Objects/Frame.o
			
Objects/resources.o: ../../samples/wxFlatNotebook/resources.cpp
	$(CMP) $(CXXFLAGS) -c ../../samples/wxFlatNotebook/resources.cpp -o Objects/resources.o

clean: 
	${RM} $(TEST_OBJ) $(OUTPUT)
	${RM} $(OBJ) $(LIB_OUTPUT)
